#include "sklc_lib/vector/vector.h"
#include <stdio.h>

int main() {
    vector vector_of_vectors = vector_create(vector);
    for (int i = 0; i < 10; ++i) {
        vector inner_vector = vector_create(int);
        for (int j = 0; j < 100; ++j) {
            inner_vector.push_back(&inner_vector, &j);     
        }
        vector_of_vectors.push_back(&vector_of_vectors, &inner_vector);
    }

    for (int i = 0; i < 10; ++i) {
        vector* print_vec_ptr = (vector*)vector_of_vectors.pop_back(&vector_of_vectors);
        if (print_vec_ptr != NULL) {
            vector print_vec = *print_vec_ptr;
            for(int j = 0; j < 100; ++j) {
                printf("Vector#%d, value#%d: %d\n", i, j, ((int*)print_vec.data)[j]);
            }
            // Destroy the vector using its address
            vector_destroy(&print_vec);
        }
    }

    vector_destroy(&vector_of_vectors);
    return 0;
}