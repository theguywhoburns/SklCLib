#include <sklc_lib/utils/chunkvec.h>

u64 Stride();

typedef struct ChunkHeader {
    u32 length;
} ChunkHeader;


ChVec ChVec_Create  (u32 max_element_size, u32 max_elements_in_chunk) {
    return ChVec_CreateEx(max_element_size, max_elements_in_chunk, 1);
}

ChVec ChVec_CreateEx(u32 max_element_size, u32 max_elements_in_chunk, u32 num_prealloc_chunks) {
    ChVec ret = {0};
    ret.chunk_vector = _vector_create(num_prealloc_chunks, max_element_size * max_elements_in_chunk + sizeof(ChunkHeader));
}