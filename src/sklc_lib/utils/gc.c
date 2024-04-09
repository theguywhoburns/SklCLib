#include <sklc_lib/utils/gc.h>

#include <sklc_lib/utils/logger.h>

#include <errno.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
//#include "primes.h"

/*
 * Set log level for this compilation unit. If set to LOGLEVEL_DEBUG,
 * the garbage collector will be very chatty.
 */
#undef LOGLEVEL
#define LOGLEVEL LOGLEVEL_INFO

/*
 * The size of a pointer.
 */
#define PTRSIZE sizeof(char*)

/*
 * Allocations can temporarily be tagged as "marked" an part of the
 * mark-and-sweep implementation or can be tagged as "roots" which are
 * not automatically garbage collected. The latter allows the implementation
 * of global variables.
 */
#define GC_TAG_NONE 0x0
#define GC_TAG_ROOT 0x1
#define GC_TAG_MARK 0x2

/*
 * Support for windows c compiler is added by adding this macro.
 * Tested on: Microsoft (R) C/C++ Optimizing Compiler Version 19.24.28314 for x86
 */
#if defined(_MSC_VER)
#define __builtin_frame_address(x)  ((void)(x), _AddressOfReturnAddress())
#endif

/*
 * Define a globally available GC object; this allows all code that
 * includes the gc.h header to access a global static garbage collector.
 * Convenient for single-threaded code, insufficient for multi-threaded
 * use cases. Use the GC_NO_GLOBAL_GC flag to toggle.
 */
#ifndef GC_NO_GLOBAL_GC
GarbageCollector gc; // global GC object
#endif


static bool is_prime(u64 n)
{
    /* https://stackoverflow.com/questions/1538644/c-determine-if-a-number-is-prime */
    if (n <= 3)
        return n > 1;     // as 2 and 3 are prime
    else if (n % 2==0 || n % 3==0)
        return false;     // check if n is divisible by 2 or 3
    else {
        for (u64 i=5; i*i<=n; i+=6) {
            if (n % i == 0 || n%(i + 2) == 0)
                return false;
        }
        return true;
    }
}

static u64 next_prime(u64 n)
{
    while (!is_prime(n)) ++n;
    return n;
}

/**
 * The allocation object.
 *
 * The allocation object holds all metadata for a memory location
 * in one place.
 */
typedef struct Allocation {
    void* ptr;                // mem pointer
    u64 size;              // allocated size in bytes
    char tag;                 // the tag for mark-and-sweep
    void (*dtor)(void*);      // destructor
    struct Allocation* next;  // separate chaining
} Allocation;

/**
 * Create a new allocation object.
 *
 * Creates a new allocation object using the system `malloc`.
 *
 * @param[in] ptr The pointer to the memory to manage.
 * @param[in] size The size of the memory range pointed to by `ptr`.
 * @param[in] dtor A pointer to a destructor function that should be called
 *                 before freeing the memory pointed to by `ptr`.
 * @returns Pointer to the new allocation instance.
 */
static Allocation* gc_allocation_new(void* ptr, u64 size, void (*dtor)(void*))
{
    Allocation* a = (Allocation*) malloc(sizeof(Allocation));
    a->ptr = ptr;
    a->size = size;
    a->tag = GC_TAG_NONE;
    a->dtor = dtor;
    a->next = NULL;
    return a;
}

/**
 * Delete an allocation object.
 *
 * Deletes the allocation object pointed to by `a`, but does *not*
 * free the memory pointed to by `a->ptr`.
 *
 * @param a The allocation object to delete.
 */
static void gc_allocation_delete(Allocation* a)
{
    free(a);
}

/**
 * The allocation hash map.
 *
 * The core data structure is a hash map that holds the allocation
 * objects and allows O(1) retrieval given the memory location. Collision
 * resolution is implemented using separate chaining.
 */
typedef struct AllocationMap {
    u64 capacity;
    u64 min_capacity;
    double downsize_factor;
    double upsize_factor;
    double sweep_factor;
    u64 sweep_limit;
    u64 size;
    Allocation** allocs;
} AllocationMap;

/**
 * Determine the current load factor of an `AllocationMap`.
 *
 * Calculates the load factor of the hash map as the quotient of the size and
 * the capacity of the hash map.
 *
 * @param am The allocationo map to calculate the load factor for.
 * @returns The load factor of the allocation map `am`.
 */
static double gc_allocation_map_load_factor(AllocationMap* am)
{
    return (double) am->size / (double) am->capacity;
}

static AllocationMap* gc_allocation_map_new(u64 min_capacity,
        u64 capacity,
        double sweep_factor,
        double downsize_factor,
        double upsize_factor)
{
    AllocationMap* am = (AllocationMap*) malloc(sizeof(AllocationMap));
    am->min_capacity = next_prime(min_capacity);
    am->capacity = next_prime(capacity);
    if (am->capacity < am->min_capacity) am->capacity = am->min_capacity;
    am->sweep_factor = sweep_factor;
    am->sweep_limit = (int) (sweep_factor * am->capacity);
    am->downsize_factor = downsize_factor;
    am->upsize_factor = upsize_factor;
    am->allocs = (Allocation**) calloc(am->capacity, sizeof(Allocation*));
    am->size = 0;
    SKLDEBUG("Created allocation map (cap=%ld, siz=%ld)", am->capacity, am->size);
    return am;
}

static void gc_allocation_map_delete(AllocationMap* am)
{
    // Iterate over the map
    SKLDEBUG("Deleting allocation map (cap=%ld, siz=%ld)",
              am->capacity, am->size);
    Allocation *alloc, *tmp;
    for (u64 i = 0; i < am->capacity; ++i) {
        alloc = am->allocs[i];
        if (alloc) {
            // Make sure to follow the chain inside a bucket
            while (alloc) {
                tmp = alloc;
                alloc = alloc->next;
                // free the management structure
                gc_allocation_delete(tmp);
            }
        }
    }
    free(am->allocs);
    free(am);
}

static u64 gc_hash(void *ptr)
{
    return ((uintptr_t)ptr) >> 3;
}

static void gc_allocation_map_resize(AllocationMap* am, u64 new_capacity)
{
    if (new_capacity <= am->min_capacity) {
        return;
    }
    // Replaces the existing items array in the hash table
    // with a resized one and pushes items into the new, correct buckets
    SKLDEBUG("Resizing allocation map (cap=%ld, siz=%ld) -> (cap=%ld)",
              am->capacity, am->size, new_capacity);
    Allocation** resized_allocs = calloc(new_capacity, sizeof(Allocation*));

    for (u64 i = 0; i < am->capacity; ++i) {
        Allocation* alloc = am->allocs[i];
        while (alloc) {
            Allocation* next_alloc = alloc->next;
            u64 new_index = gc_hash(alloc->ptr) % new_capacity;
            alloc->next = resized_allocs[new_index];
            resized_allocs[new_index] = alloc;
            alloc = next_alloc;
        }
    }
    free(am->allocs);
    am->capacity = new_capacity;
    am->allocs = resized_allocs;
    am->sweep_limit = am->size + ((u64)am->sweep_factor * (am->capacity - am->size));
}

static bool gc_allocation_map_reu64o_fit(AllocationMap* am)
{
    double load_factor = gc_allocation_map_load_factor(am);
    if (load_factor > am->upsize_factor) {
        SKLDEBUG("Load factor %0.3g > %0.3g. Triggering upsize.",
                  load_factor, am->upsize_factor);
        gc_allocation_map_resize(am, next_prime(am->capacity * 2));
        return true;
    }
    if (load_factor < am->downsize_factor) {
        SKLDEBUG("Load factor %0.3g < %0.3g. Triggering downsize.",
                  load_factor, am->downsize_factor);
        gc_allocation_map_resize(am, next_prime(am->capacity / 2));
        return true;
    }
    return false;
}

static Allocation* gc_allocation_map_get(AllocationMap* am, void* ptr)
{
    u64 index = gc_hash(ptr) % am->capacity;
    Allocation* cur = am->allocs[index];
    while(cur) {
        if (cur->ptr == ptr) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

static Allocation* gc_allocation_map_put(AllocationMap* am,
        void* ptr,
        u64 size,
        void (*dtor)(void*))
{
    u64 index = gc_hash(ptr) % am->capacity;
    SKLDEBUG("PUT request for allocation ix=%ld", index);
    Allocation* alloc = gc_allocation_new(ptr, size, dtor);
    Allocation* cur = am->allocs[index];
    Allocation* prev = NULL;
    /* Upsert if ptr is already known (e.g. dtor update). */
    while(cur != NULL) {
        if (cur->ptr == ptr) {
            // found it
            alloc->next = cur->next;
            if (!prev) {
                // position 0
                am->allocs[index] = alloc;
            } else {
                // in the list
                prev->next = alloc;
            }
            gc_allocation_delete(cur);
            SKLDEBUG("AllocationMap Upsert at ix=%ld", index);
            return alloc;

        }
        prev = cur;
        cur = cur->next;
    }
    /* Insert at the front of the separate chaining list */
    cur = am->allocs[index];
    alloc->next = cur;
    am->allocs[index] = alloc;
    am->size++;
    SKLDEBUG("AllocationMap insert at ix=%ld", index);
    void* p = alloc->ptr;
    if (gc_allocation_map_reu64o_fit(am)) {
        alloc = gc_allocation_map_get(am, p);
    }
    return alloc;
}


static void gc_allocation_map_remove(AllocationMap* am,
                                     void* ptr,
                                     bool allow_resize)
{
    // ignores unknown keys
    u64 index = gc_hash(ptr) % am->capacity;
    Allocation* cur = am->allocs[index];
    Allocation* prev = NULL;
    Allocation* next;
    while(cur != NULL) {
        next = cur->next;
        if (cur->ptr == ptr) {
            // found it
            if (!prev) {
                // first item in list
                am->allocs[index] = cur->next;
            } else {
                // not the first item in the list
                prev->next = cur->next;
            }
            gc_allocation_delete(cur);
            am->size--;
        } else {
            // move on
            prev = cur;
        }
        cur = next;
    }
    if (allow_resize) {
        gc_allocation_map_reu64o_fit(am);
    }
}


static void* gc_mcalloc(u64 count, u64 size)
{
    if (!count) return malloc(size);
    return calloc(count, size);
}

static bool gc_needs_sweep(GarbageCollector* _gc)
{
    return _gc->allocs->size > _gc->allocs->sweep_limit;
}

static void* gc_allocate(GarbageCollector* _gc, u64 count, u64 size, void(*dtor)(void*))
{
    /* Allocation logic that generalizes over malloc/calloc. */

    /* Check if we reached the high-water mark and need to clean up */
    if (gc_needs_sweep(_gc) && !_gc->paused) {
        u64 freed_mem = gc_run(_gc);
        SKLDEBUG("Garbage collection cleaned up %lu bytes.", freed_mem);
    }
    /* With cleanup out of the way, attempt to allocate memory */
    void* ptr = gc_mcalloc(count, size);
    u64 alloc_size = count ? count * size : size;
    /* If allocation fails, force an out-of-policy run to free some memory and try again. */
    if (!ptr && !_gc->paused && (errno == EAGAIN || errno == ENOMEM)) {
        gc_run(_gc);
        ptr = gc_mcalloc(count, size);
    }
    /* Start managing the memory we received from the system */
    if (ptr) {
        SKLDEBUG("Allocated %zu bytes at %p", alloc_size, (void*) ptr);
        Allocation* alloc = gc_allocation_map_put(_gc->allocs, ptr, alloc_size, dtor);
        /* Deal with metadata allocation failure */
        if (alloc) {
            SKLDEBUG("Managing %zu bytes at %p", alloc_size, (void*) alloc->ptr);
            ptr = alloc->ptr;
        } else {
            /* We failed to allocate the metadata, fail cleanly. */
            free(ptr);
            ptr = NULL;
        }
    }
    return ptr;
}

static void gc_make_root(GarbageCollector* _gc, void* ptr)
{
    Allocation* alloc = gc_allocation_map_get(_gc->allocs, ptr);
    if (alloc) {
        alloc->tag |= GC_TAG_ROOT;
    }
}

void* gc_malloc(GarbageCollector*_gc, u64 size)
{
    return gc_malloc_ext(_gc, size, NULL);
}

void* gc_malloc_static(GarbageCollector* _gc, u64 size, void(*dtor)(void*))
{
    void* ptr = gc_malloc_ext(_gc, size, dtor);
    gc_make_root(_gc, ptr);
    return ptr;
}

void* gc_make_static(GarbageCollector* _gc, void* ptr)
{
    gc_make_root(_gc, ptr);
    return ptr;
}

void* gc_malloc_ext(GarbageCollector* _gc, u64 size, void(*dtor)(void*))
{
    return gc_allocate(_gc, 0, size, dtor);
}


void* gc_calloc(GarbageCollector* _gc, u64 count, u64 size)
{
    return gc_calloc_ext(_gc, count, size, NULL);
}


void* gc_calloc_ext(GarbageCollector* _gc, u64 count, u64 size,
                    void(*dtor)(void*))
{
    return gc_allocate(_gc, count, size, dtor);
}


void* gc_realloc(GarbageCollector* _gc, void* p, u64 size)
{
    Allocation* alloc = gc_allocation_map_get(_gc->allocs, p);
    if (p && !alloc) {
        // the user passed an unknown pointer
        errno = EINVAL;
        return NULL;
    }
    void* q = realloc(p, size);
    if (!q) {
        // realloc failed but p is still valid
        return NULL;
    }
    if (!p) {
        // allocation, not reallocation
        alloc = gc_allocation_map_put(_gc->allocs, q, size, NULL);
        return alloc->ptr;
    }
    if (p == q) {
        // successful reallocation w/o copy
        alloc->size = size;
    } else {
        // successful reallocation w/ copy
        void (*dtor)(void*) = alloc->dtor;
        gc_allocation_map_remove(_gc->allocs, p, true);
        gc_allocation_map_put(_gc->allocs, q, size, dtor);
    }
    return q;
}

void gc_free(GarbageCollector* _gc, void* ptr)
{
    Allocation* alloc = gc_allocation_map_get(_gc->allocs, ptr);
    if (alloc) {
        if (alloc->dtor) {
            alloc->dtor(ptr);
        }
        free(ptr);
        gc_allocation_map_remove(_gc->allocs, ptr, true);
    } else {
        SKLWARN("Ignoring request to free unknown pointer %p", (void*) ptr);
    }
}

void gc_start(GarbageCollector* _gc, void* bos)
{
    gc_start_ext(_gc, bos, 1024, 1024, 0.2, 0.8, 0.5);
}

void gc_start_ext(GarbageCollector* _gc,
                  void* bos,
                  u64 initial_capacity,
                  u64 min_capacity,
                  double downsize_load_factor,
                  double upsize_load_factor,
                  double sweep_factor)
{
    double downsize_limit = downsize_load_factor > 0.0 ? downsize_load_factor : 0.2;
    double upsize_limit = upsize_load_factor > 0.0 ? upsize_load_factor : 0.8;
    sweep_factor = sweep_factor > 0.0 ? sweep_factor : 0.5;
    _gc->paused = false;
    _gc->bos = bos;
    initial_capacity = initial_capacity < min_capacity ? min_capacity : initial_capacity;
    _gc->allocs = gc_allocation_map_new(min_capacity, initial_capacity,
                                       sweep_factor, downsize_limit, upsize_limit);
    SKLDEBUG("Created new garbage collector (cap=%ld, siz=%ld).", _gc->allocs->capacity,
              _gc->allocs->size);
}

void gc_pause(GarbageCollector* _gc)
{
    _gc->paused = true;
}

void gc_resume(GarbageCollector* _gc)
{
    _gc->paused = false;
}

void gc_mark_alloc(GarbageCollector* _gc, void* ptr)
{
    Allocation* alloc = gc_allocation_map_get(_gc->allocs, ptr);
    /* Mark if alloc exists and is not tagged already, otherwise skip */
    if (alloc && !(alloc->tag & GC_TAG_MARK)) {
        SKLDEBUG("Marking allocation (ptr=%p)", ptr);
        alloc->tag |= GC_TAG_MARK;
        /* Iterate over allocation contents and mark them as well */
        SKLDEBUG("Checking allocation (ptr=%p, size=%lu) contents", ptr, alloc->size);
        for (char* p = (char*) alloc->ptr;
                p <= (char*) alloc->ptr + alloc->size - PTRSIZE;
                ++p) {
            SKLDEBUG("Checking allocation (ptr=%p) @%lu with value %p",
                      ptr, p-((char*) alloc->ptr), *(void**)p);
            gc_mark_alloc(_gc, *(void**)p);
        }
    }
}

void gc_mark_stack(GarbageCollector* _gc)
{
    SKLDEBUG("Marking the stack (gc@%p) in increments of %ld", (void*)_gc, sizeof(char));
    void *tos = __builtin_frame_address(0);
    void *bos = _gc->bos;
    /* The stack grows towards smaller memory addresses, hence we scan tos->bos.
     * Stop scanning once the distance between tos & bos is too small to hold a valid pointer */
    for (char* p = (char*) tos; p <= (char*) bos - PTRSIZE; ++p) {
        gc_mark_alloc(_gc, *(void**)p);
    }
}

void gc_mark_roots(GarbageCollector* _gc)
{
    SKLDEBUG("Marking roots%s", "");
    for (u64 i = 0; i < _gc->allocs->capacity; ++i) {
        Allocation* chunk = _gc->allocs->allocs[i];
        while (chunk) {
            if (chunk->tag & GC_TAG_ROOT) {
                SKLDEBUG("Marking root @ %p", chunk->ptr);
                gc_mark_alloc(_gc, chunk->ptr);
            }
            chunk = chunk->next;
        }
    }
}

void gc_mark(GarbageCollector* _gc)
{
    /* Note: We only look at the stack and the heap, and ignore BSS. */
    SKLDEBUG("Initiating GC mark (gc@%p)", (void*) _gc);
    /* Scan the heap for roots */
    gc_mark_roots(_gc);
    /* Dump registers onto stack and scan the stack */
    void (*volatile _mark_stack)(GarbageCollector*) = gc_mark_stack;
    jmp_buf ctx;
    memset(&ctx, 0, sizeof(jmp_buf));
    setjmp(ctx);
    _mark_stack(_gc);
}

u64 gc_sweep(GarbageCollector* _gc)
{
    SKLDEBUG("Initiating GC sweep (gc@%p)", (void*) _gc);
    u64 total = 0;
    for (u64 i = 0; i < _gc->allocs->capacity; ++i) {
        Allocation* chunk = _gc->allocs->allocs[i];
        Allocation* next = NULL;
        /* Iterate over separate chaining */
        while (chunk) {
            if (chunk->tag & GC_TAG_MARK) {
                SKLDEBUG("Found used allocation %p (ptr=%p)", (void*) chunk, (void*) chunk->ptr);
                /* unmark */
                chunk->tag &= ~GC_TAG_MARK;
                chunk = chunk->next;
            } else {
                SKLDEBUG("Found unused allocation %p (%lu bytes @ ptr=%p)", (void*) chunk, chunk->size, (void*) chunk->ptr);
                /* no reference to this chunk, hence delete it */
                total += chunk->size;
                if (chunk->dtor) {
                    chunk->dtor(chunk->ptr);
                }
                free(chunk->ptr);
                /* and remove it from the bookkeeping */
                next = chunk->next;
                gc_allocation_map_remove(_gc->allocs, chunk->ptr, false);
                chunk = next;
            }
        }
    }
    gc_allocation_map_reu64o_fit(_gc->allocs);
    return total;
}

/**
 * Unset the ROOT tag on all roots on the heap.
 *
 * @param gc A pointer to a garbage collector instance.
 */
void gc_unroot_roots(GarbageCollector* _gc)
{
    SKLDEBUG("Unmarking roots%s", "");
    for (u64 i = 0; i < _gc->allocs->capacity; ++i) {
        Allocation* chunk = _gc->allocs->allocs[i];
        while (chunk) {
            if (chunk->tag & GC_TAG_ROOT) {
                chunk->tag &= ~GC_TAG_ROOT;
            }
            chunk = chunk->next;
        }
    }
}

u64 gc_stop(GarbageCollector* _gc)
{
    gc_unroot_roots(_gc);
    u64 collected = gc_sweep(_gc);
    gc_allocation_map_delete(_gc->allocs);
    return collected;
}

u64 gc_run(GarbageCollector* _gc)
{
    SKLDEBUG("Initiating GC run (gc@%p)", (void*) _gc);
    gc_mark(_gc);
    return gc_sweep(_gc);
}

char* gc_strdup (GarbageCollector* _gc, const char* s)
{
    u64 len = strlen(s) + 1;
    void *new = gc_malloc(_gc, len);

    if (new == NULL) {
        return NULL;
    }
    return (char*) memcpy(new, s, len);
}
