#include "../include/lrps.h"
#include <stdio.h>

int main() {
    int a, b, c, d;
    
    printf("Enter a b c d: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    Formula result = find_formula(a, b, c, d);
    show_formula(result);
    
    return 0;
}