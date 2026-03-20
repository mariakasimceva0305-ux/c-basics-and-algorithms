#include "permutation.h"
#include <stdlib.h>
#include <limits.h>

static size_t random_range(size_t upper) {
    if (upper <= 1) return 0;
    
    size_t limit = RAND_MAX / upper * upper;
    size_t r;
    do {
        r = rand();
    } while (r >= limit);
    
    return r % upper;
}

static void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permutation_init(unsigned int seed) {
    srand(seed);
}

int* generate_permutation(int n) {
    if (n <= 0) return NULL;
    
    if (n > 1000000) return NULL; 
    
    int* perm = (int*)malloc((size_t)n * sizeof(int));
    if (!perm) return NULL;
    
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    
    for (int i = n - 1; i > 0; i--) {
        size_t j = random_range((size_t)i + 1);
        swap(&perm[i], &perm[j]);
    }
    
    return perm;
}

void free_permutation(int* perm) {
    free(perm);
}