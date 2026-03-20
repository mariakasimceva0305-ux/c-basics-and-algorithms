#include "../include/permutation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void test_permutation_uniformity_small() {
    permutation_init(42);
    int n = 3;
    int counts[6][3] = {0}; 
    
    
    for (int trial = 0; trial < 6000; trial++) {
        int* p = generate_permutation(n);
        
        
        int idx = -1;
        if (p[0]==0 && p[1]==1 && p[2]==2) idx = 0;
        else if (p[0]==0 && p[1]==2 && p[2]==1) idx = 1;
        else if (p[0]==1 && p[1]==0 && p[2]==2) idx = 2;
        else if (p[0]==1 && p[1]==2 && p[2]==0) idx = 3;
        else if (p[0]==2 && p[1]==0 && p[2]==1) idx = 4;
        else if (p[0]==2 && p[1]==1 && p[2]==0) idx = 5;
        
        assert(idx != -1); 
        counts[idx][0]++; 
        
        free_permutation(p);
    }
    
   
    for (int i = 0; i < 6; i++) {
        assert(counts[i][0] > 800 && counts[i][0] < 1200); // ±20% допуск
    }
}

void test_permutation_reproducibility() {
    permutation_init(12345);
    int* p1 = generate_permutation(5);
    
    permutation_init(12345); // Тот же seed
    int* p2 = generate_permutation(5);
    
    // Должны быть идентичны
    for (int i = 0; i < 5; i++) {
        assert(p1[i] == p2[i]);
    }
    
    free_permutation(p1);
    free_permutation(p2);
}

void test_permutation_different_seeds() {
    permutation_init(111);
    int* p1 = generate_permutation(10);
    
    permutation_init(222); // Другой seed
    int* p2 = generate_permutation(10);
    
   
    int different = 0;
    for (int i = 0; i < 10; i++) {
        if (p1[i] != p2[i]) {
            different = 1;
            break;
        }
    }
    assert(different == 1);
    
    free_permutation(p1);
    free_permutation(p2);
}

void test_permutation_large_n() {
    permutation_init(42);
    int n = 10000;
    int* p = generate_permutation(n);
    assert(p != NULL);
    
    int* seen = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        assert(p[i] >= 0 && p[i] < n);
        assert(seen[p[i]] == 0); 
        seen[p[i]] = 1;
    }
    
    free(seen);
    free_permutation(p);
}

void test_permutation_edge_cases() {
    // n = 1
    permutation_init(42);
    int* p1 = generate_permutation(1);
    assert(p1 != NULL);
    assert(p1[0] == 0);
    free_permutation(p1);
    
    // n = 0
    int* p2 = generate_permutation(0);
    assert(p2 == NULL);
    
    // n отрицательное
    int* p3 = generate_permutation(-5);
    assert(p3 == NULL);
    
    // Очень большое n 
    int* p4 = generate_permutation(INT_MAX);
    assert(p4 == NULL);
}

void test_permutation_multiple_calls() {
    permutation_init(42);
    
    for (int i = 0; i < 100; i++) {
        int* p = generate_permutation(10);
        assert(p != NULL);
        
        int sum = 0;
        for (int j = 0; j < 10; j++) {
            sum += p[j];
        }
        assert(sum == 45); // 0+1+2+...+9 = 45
        
        free_permutation(p);
    }
}

void run_all_tests() {
    test_permutation_edge_cases();
    test_permutation_multiple_calls();
    test_permutation_large_n();
    test_permutation_reproducibility();
    test_permutation_different_seeds();
    test_permutation_uniformity_small();
    printf("All tests passed!\n");
}