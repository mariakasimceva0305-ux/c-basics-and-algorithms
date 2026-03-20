#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "zhg_poly.h"

int zhg_poly(const int *func, int n, int *coeff) {
   
    if (n < 0) {
        fprintf(stderr, "Error: n cannot be negative\n");
        return -1;
    }
    
    if (func == NULL || coeff == NULL) {
        fprintf(stderr, "Error: NULL pointer input\n");
        return -1;
    }
    
   
    if (n >= sizeof(size_t) * CHAR_BIT) {
        fprintf(stderr, "Error: n is too large\n");
        return -1;
    }
    
    size_t size = (size_t)1 << n;
    
    for (size_t i = 0; i < size; i++) {
        if (func[i] != 0 && func[i] != 1) {
            fprintf(stderr, "Error: function values must be 0 or 1\n");
            return -1;
        }
    }
    
    int *temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return -1;
    }
    
    memcpy(temp, func, size * sizeof(int));
    
    for (size_t block_size = 1; block_size < size; block_size <<= 1) {
        for (size_t i = 0; i < size; i += block_size << 1) {
            for (size_t j = 0; j < block_size; j++) {
                temp[i + j + block_size] ^= temp[i + j];
            }
        }
    }
    
    memcpy(coeff, temp, size * sizeof(int));
    free(temp);
    return 0;
}