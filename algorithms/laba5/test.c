#include "../include/lrps.h"
#include <stdio.h>
#include <math.h>

void test_case(int a, int b, int c, int d, char* name) {
    printf("Test: %s \n", name);
    printf("Input: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
    
    Formula res = find_formula(a, b, c, d);
    show_formula(res);
    
    printf("Check: ");
    if (res.case_type == 1) {
        double x3 = res.coef1 * res.r1 * res.r1 + res.coef2 * res.r2 * res.r2;
        double x4 = res.coef1 * res.r1 * res.r1 * res.r1 + res.coef2 * res.r2 * res.r2 * res.r2;
        printf("x3=%.2f, x4=%.2f", x3, x4);
    } else if (res.case_type == 2) {
        double x3 = (res.coef1 + res.coef2 * 2) * res.r1 * res.r1;
        double x4 = (res.coef1 + res.coef2 * 3) * res.r1 * res.r1 * res.r1;
        printf("x3=%.2f, x4=%.2f", x3, x4);
    }
    printf("\n\n");
}

int main() {
    printf("tests\n\n");
    
    test_case(1, 1, 1, 1, "Fibonacci");
    test_case(2, -1, 1, 3, "Arithmetic progression");
    test_case(3, 0, 2, 6, "Geometric progression");
    test_case(4, -4, 1, 4, "Multiple roots");
    test_case(-2, 3, 1, 1, "Negative coefficients");
    test_case(0, 2, 1, 2, "a = 0");
    test_case(2, 0, 3, 6, "b = 0");
    test_case(0, 0, 5, 5, "Zero sequence");
    
    printf("All tests done\n");
    return 0;
}