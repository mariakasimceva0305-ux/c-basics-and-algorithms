#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "zhg_poly.h"

void print_coeff(const int *coeff, int size, const char *name) {
    printf("%s: [", name);
    for (int i = 0; i < size; i++) {
        printf("%d", coeff[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void test_zero_vars() {
    printf("Testing zero variables...\n");
    int func[] = {1};
    int coeff[1];
    assert(zhg_poly(func, 0, coeff) == 0);
    print_coeff(coeff, 1, "Zero vars result");
    assert(coeff[0] == 1);
    printf("OK\n\n");
}

void test_one_var_identity() {
    printf("Testing one variable (identity)...\n");
    int func[] = {0, 1};  // f(x) = x
    int coeff[2];
    assert(zhg_poly(func, 1, coeff) == 0);
    print_coeff(coeff, 2, "One var identity result");
    assert(coeff[0] == 0 && coeff[1] == 1);
    printf("OK\n\n");
}

void test_one_var_negation() {
    printf("Testing one variable (negation)...\n");
    int func[] = {1, 0};  // f(x) = ¬x = 1 ⊕ x
    int coeff[2];
    assert(zhg_poly(func, 1, coeff) == 0);
    print_coeff(coeff, 2, "One var negation result");
    assert(coeff[0] == 1 && coeff[1] == 1);
    printf("OK\n\n");
}

void test_and() {
    printf("Testing AND function...\n");
    int func[] = {0, 0, 0, 1};  // f(x,y) = x ∧ y
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "AND result");
    assert(coeff[0] == 0 && coeff[1] == 0 && coeff[2] == 0 && coeff[3] == 1);
    printf("OK\n\n");
}

void test_or() {
    printf("Testing OR function...\n");
    int func[] = {0, 1, 1, 1};  // f(x,y) = x ∨ y = x ⊕ y ⊕ xy
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "OR result");
    // Полином: x ⊕ y ⊕ xy
    assert(coeff[0] == 0 && coeff[1] == 1 && coeff[2] == 1 && coeff[3] == 1);
    printf("OK\n\n");
}

void test_xor() {
    printf("Testing XOR function...\n");
    int func[] = {0, 1, 1, 0};  // f(x,y) = x ⊕ y
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "XOR result");
    // Полином: x ⊕ y
    assert(coeff[0] == 0 && coeff[1] == 1 && coeff[2] == 1 && coeff[3] == 0);
    printf("OK\n\n");
}

void test_implication() {
    printf("Testing implication...\n");
    int func[] = {1, 1, 0, 1};  // f(x,y) = x → y = ¬x ∨ y = 1 ⊕ x ⊕ xy
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "Implication result");
    // Полином: 1 ⊕ x ⊕ xy
    assert(coeff[0] == 1 && coeff[1] == 0 && coeff[2] == 1 && coeff[3] == 1);
    printf("OK\n\n");
}

void test_const_one() {
    printf("Testing constant one...\n");
    int func[] = {1, 1, 1, 1};
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "Const one result");
    assert(coeff[0] == 1 && coeff[1] == 0 && coeff[2] == 0 && coeff[3] == 0);
    printf("OK\n\n");
}

void test_const_zero() {
    printf("Testing constant zero...\n");
    int func[] = {0, 0, 0, 0};
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "Const zero result");
    assert(coeff[0] == 0 && coeff[1] == 0 && coeff[2] == 0 && coeff[3] == 0);
    printf("OK\n\n");
}

void test_majority_3() {
    printf("Testing majority function (3 variables)...\n");
    // f(x,y,z) = (x∧y) ∨ (x∧z) ∨ (y∧z) = xy ⊕ xz ⊕ yz
    int func[] = {0, 0, 0, 1, 0, 1, 1, 1};
    int coeff[8];
    assert(zhg_poly(func, 3, coeff) == 0);
    print_coeff(coeff, 8, "Majority 3 result");
    int expected[] = {0, 0, 0, 1, 0, 1, 1, 0};
    for (int i = 0; i < 8; i++) {
        if (coeff[i] != expected[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n", i, expected[i], coeff[i]);
        }
        assert(coeff[i] == expected[i]);
    }
    printf("OK\n\n");
}

void test_parity_3() {
    printf("Testing parity function (3 variables)...\n");
    // f(x,y,z) = x ⊕ y ⊕ z
    int func[] = {0, 1, 1, 0, 1, 0, 0, 1};
    int coeff[8];
    assert(zhg_poly(func, 3, coeff) == 0);
    print_coeff(coeff, 8, "Parity 3 result");
    int expected[] = {0, 1, 1, 0, 1, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        if (coeff[i] != expected[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n", i, expected[i], coeff[i]);
        }
        assert(coeff[i] == expected[i]);
    }
    printf("OK\n\n");
}

void test_custom_function() {
    printf("Testing custom function...\n");
    // Пример из задания: f(x,y,z) = 1 ⊕ x ⊕ y ⊕ z
    int func[] = {1, 0, 0, 1, 0, 1, 1, 0};
    int coeff[8];
    assert(zhg_poly(func, 3, coeff) == 0);
    print_coeff(coeff, 8, "Custom function result");
    // Полином: 1 ⊕ x ⊕ y ⊕ z
    int expected[] = {1, 1, 1, 0, 1, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        if (coeff[i] != expected[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n", i, expected[i], coeff[i]);
        }
        assert(coeff[i] == expected[i]);
    }
    printf("OK\n\n");
}

void test_large_n() {
    printf("Testing n=10 (1024 values)...\n");
    int n = 10;
    size_t size = 1 << n;
    int *func = (int*)malloc(size * sizeof(int));
    int *coeff = (int*)malloc(size * sizeof(int));

    for (size_t i = 0; i < size; i++) {
        int parity = 0;
        unsigned int val = i;
        while (val) {
            parity ^= (val & 1);
            val >>= 1;
        }
        func[i] = parity;
    }
    
    assert(zhg_poly(func, n, coeff) == 0);
    
    int correct = 1;
    for (size_t i = 0; i < size; i++) {
        int weight = 0;
        unsigned int val = i;
        while (val) {
            weight += (val & 1);
            val >>= 1;
        }
        
        if ((weight == 1 && coeff[i] != 1) || (weight != 1 && coeff[i] != 0)) {
            correct = 0;
            break;
        }
    }
    
    assert(correct == 1);
    free(func);
    free(coeff);
    printf("OK\n\n");
}

void test_invalid_n_negative() {
    printf("Testing negative n...\n");
    int func[] = {1};
    int coeff[1];
    assert(zhg_poly(func, -1, coeff) == -1);
    printf("OK\n\n");
}

void test_invalid_null_func() {
    printf("Testing NULL function pointer...\n");
    int coeff[1];
    assert(zhg_poly(NULL, 0, coeff) == -1);
    printf("OK\n\n");
}

void test_invalid_null_coeff() {
    printf("Testing NULL coefficients pointer...\n");
    int func[] = {1};
    assert(zhg_poly(func, 0, NULL) == -1);
    printf("OK\n\n");
}

void test_invalid_function_values() {
    printf("Testing invalid function values...\n");
    int func[] = {0, 2, 1, 1};
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == -1);
    printf("OK\n\n");
}

void test_empty_function() {
    printf("Testing empty function (n=0)...\n");
    int func[] = {0};
    int coeff[1];
    assert(zhg_poly(func, 0, coeff) == 0);
    assert(coeff[0] == 0);
    printf("OK\n\n");
}

void test_nand_function() {
    printf("Testing NAND function...\n");
    int func[] = {1, 1, 1, 0};  // f(x,y) = ¬(x ∧ y) = 1 ⊕ xy
    int coeff[4];
    assert(zhg_poly(func, 2, coeff) == 0);
    print_coeff(coeff, 4, "NAND result");
    // Полином: 1 ⊕ xy
    assert(coeff[0] == 1 && coeff[1] == 0 && coeff[2] == 0 && coeff[3] == 1);
    printf("OK\n\n");
}

void run_all_tests() {
    printf("Starting all tests for Zhegalkin polynomial\n");
    
    test_zero_vars();
    test_one_var_identity();
    test_one_var_negation();
    test_and();
    test_or();
    test_xor();
    test_implication();
    test_const_one();
    test_const_zero();
    test_majority_3();
    test_parity_3();
    test_custom_function();
    test_nand_function();
    test_empty_function();
    
    // Большие тесты
    test_large_n();
    
    // Тесты ошибок
    test_invalid_n_negative();
    test_invalid_null_func();
    test_invalid_null_coeff();
    test_invalid_function_values();
    printf("All tests passed successfully!\n");
}

int main() {
    run_all_tests();
    return 0;
}