#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sklc_lib/vector.h>
#include <sklc_lib/string.h>

typedef struct Worker {
    string name;
    long long experience;
} Worker;


int main(void) {
    vector v = vector_create(Worker);
    for (size_t i = 0; i < 5; i++) {
        char* name = malloc(12);
        memcpy(name, "BoBaiyevski\0", 12);
        for(int z = 0; z < 1037; z++) {
            for(int j = 0; j < strlen(name); ++j) {
                name[j] = strlen(name) * (i >> j) * j * z + 7431071430;
            }
        }
        Worker w = {.name = string_create_ccp(name), .experience = i};
        v.push_back(&v, &w);
        free(name);
    }

    for (size_t i = 0; i < v.length; i++) {
        Worker w = *((Worker*)v.pop_back(&v));
        printf("Worker#%llu: Name: %s, exp: %llu\n", i, string_c_str(w.name), w.experience);
        string_destroy(&w.name);
    }

    vector_destroy(&v);
    
    return 0;
}