#include <sklc_lib/utils/tinyvec.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* _tinyvec_create(u64 length, u64 stride) {
    u64 header_size = TINYVEC_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = malloc(header_size + array_size);
    memset(new_array, 0, header_size + array_size);
    new_array[TINYVEC_CAPACITY] = length;
    new_array[TINYVEC_LENGTH] = 0;
    new_array[TINYVEC_STRIDE] = stride;
    return (void*)(new_array + TINYVEC_FIELD_LENGTH);
}

void _tinyvec_destroy(void* array) {
    if(!array) return;
    u64* header = (u64*) array - TINYVEC_FIELD_LENGTH;
    free(header);
}

u64 _tinyvec_field_get(void* array, u64 field) {
    u64* header = (u64*) array - TINYVEC_FIELD_LENGTH;
    return header[field];
}

void _tinyvec_field_set(void* array, u64 field, u64 value) {
    u64* header = (u64*) array - TINYVEC_FIELD_LENGTH;
    header[field] = value;
}


void* _tinyvec_resize(void* tinyvec, u64 size) {
    u64 length = _tinyvec_field_get(tinyvec, TINYVEC_LENGTH);
    u64 stride = _tinyvec_field_get(tinyvec, TINYVEC_STRIDE);
    void* temp = _tinyvec_create(size, stride);
    memcpy(temp, tinyvec, size * stride);
    _tinyvec_field_set(temp, TINYVEC_LENGTH, length);
    _tinyvec_destroy(tinyvec);
    return temp;
}

void* _tinyvec_reserve(void* tinyvec, u64 size) {
    u64 length = _tinyvec_field_get(tinyvec, TINYVEC_LENGTH);
    u64 stride = _tinyvec_field_get(tinyvec, TINYVEC_STRIDE);
    void* temp = _tinyvec_create((_tinyvec_field_get(tinyvec, TINYVEC_CAPACITY) + size), stride);
    memcpy(temp, tinyvec, length * stride);
    _tinyvec_field_set(temp, TINYVEC_LENGTH, length);
    _tinyvec_destroy(tinyvec);
    return temp;
}

void* _tinyvec_push(void* array, const void* value_ptr) {
    u64 length = tinyvec_length(array);
    u64 stride = tinyvec_stride(array);
    if(length >= tinyvec_capacity(array)) {
        array = _tinyvec_reserve(array, TINYVEC_RESIZE_FACTOR);
    }
    u64 addr = (u64)array;
    addr += (length * stride);
    memcpy((void*)addr, value_ptr, stride);
    _tinyvec_field_set(array, TINYVEC_LENGTH, length + 1);
    return array;
}

void _tinyvec_pop(void* array, void* dest) {
    u64 length = tinyvec_length(array);
    u64 stride = tinyvec_stride(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    memcpy(dest, (void*)addr, stride);
    _tinyvec_field_set(array, TINYVEC_LENGTH, length - 1);
}

void* _tinyvec_pop_at(void* array, u64 index, void* dest) {
    u64 length = tinyvec_length(array);
    u64 stride = tinyvec_stride(array);
    if(index >= length) {
        printf("Index outside the bounds of this array! Length:%lli, index: %lli\n", length, index);
        return array;
    }
    u64 addr = (u64)array;
    memcpy(dest, (void*)(addr + (index * stride)), stride);
    if(index != length -1) {
        memcpy((void*)(addr +(index * stride)),(void*)(addr +((index + 1) * stride)),stride * (length - index));
    }
    _tinyvec_field_set(array, TINYVEC_LENGTH, length - 1);
    return array;
}

void* _tinyvec_insert_at(void* array, u64 index, void* value_ptr) {
    u64 length = tinyvec_length(array);
    u64 stride = tinyvec_stride(array);
    if(index >= length) {
        printf("Index outside the bounds of this array! Length:%lli, index: %lli\n", length, index);
        return array;
    }
    if(length >= tinyvec_capacity(array)) {
        array = _tinyvec_reserve(array, TINYVEC_RESIZE_FACTOR);
    }
    u64 addr = (u64)array;
    if(index != length -1) {
        memcpy((void*)(addr + ((index + 1) * stride)),(void*)(addr + (index * stride)),stride * (length - index));
    }
    memcpy((void*)(addr + ((index + 1) * stride)), value_ptr, stride);
    _tinyvec_field_set(array, TINYVEC_LENGTH, length + 1);
    return array;
}
