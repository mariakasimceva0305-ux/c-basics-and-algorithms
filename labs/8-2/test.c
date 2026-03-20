#include "include/permutation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void test_permutation_uniformity_small(void);
void test_permutation_reproducibility(void);
void test_permutation_different_seeds(void);
void test_permutation_large_n(void);
void test_permutation_edge_cases(void);
void test_permutation_multiple_calls(void);
void run_all_tests(void);

int main() {
    run_all_tests();
    return 0;
}