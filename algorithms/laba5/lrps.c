#include "../include/lrps.h"
#include <math.h>
#include <stdio.h>
#include <float.h>

// Вспомогательные функции
static void print_term(double coef, double base, int is_first);
static void print_power(double base);
static int is_zero(double x);

Formula find_formula(int a, int b, int c, int d) {
    Formula result = {0};
    
    // Характеристическое уравнение: r² - a*r - b = 0
    // Дискриминант: D = a² + 4b
    double discriminant = (double)(a * a) + 4.0 * (double)b;
    
    // Обработка комплексных корней
    if (discriminant < -DBL_EPSILON) {
        result.case_type = 3;
        
        // Комплексные корни: r = α ± βi
        double alpha = (double)a / 2.0;
        double beta = sqrt(-discriminant) / 2.0;
        
        result.modulus = sqrt(alpha * alpha + beta * beta);
        result.theta = atan2(beta, alpha);
        
        result.coef1 = (double)c; // C1
        
        if (is_zero(result.modulus)) {
            result.coef2 = 0.0;
        } else {
            double sin_theta = sin(result.theta);
            if (!is_zero(sin_theta)) {
                result.coef2 = ((double)d / result.modulus - result.coef1 * cos(result.theta)) / sin_theta;
            } else {
                result.coef1 = (double)d / (result.modulus * cos(result.theta));
                result.coef2 = 0.0;
            }
        }
        return result;
    }
    
    // Вещественные корни
    double root_D = sqrt(fabs(discriminant));
    
    if (discriminant >= 0) {
        result.r1 = ((double)a + root_D) / 2.0;
        result.r2 = ((double)a - root_D) / 2.0;
    } else {
        result.r1 = result.r2 = (double)a / 2.0;
    }
    
    // Проверка на кратные корни
    if (is_zero(discriminant)) {
        // Кратные корни: x_n = [C1 + C2*(n-1)] * r^(n-1)
        result.case_type = 2;
        result.coef1 = (double)c; // x1 = C1
        
        if (is_zero(result.r1)) {
            result.coef2 = (double)d; // При r=0: x2 = C2
        } else {
            result.coef2 = ((double)d - result.coef1 * result.r1) / result.r1;
        }
    } else {
        // Разные корни: x_n = C1*r1^(n-1) + C2*r2^(n-1)
        result.case_type = 1;
        
        // Система:
        double denominator = result.r1 - result.r2;
        
        if (is_zero(denominator)) {
            result.case_type = 2;
            result.coef1 = (double)c;
            result.coef2 = 0.0;
        } else {
            result.coef1 = ((double)d - (double)c * result.r2) / denominator;
            result.coef2 = ((double)c * result.r1 - (double)d) / denominator;
        }
    }
    
    return result;
}

void show_formula(Formula f) {
    switch (f.case_type) {
        case 1: {
            printf("x_n = ");
            int has_terms = 0;
            
            if (!is_zero(f.coef1)) {
                print_term(f.coef1, f.r1, 1);
                has_terms = 1;
            }
            
            if (!is_zero(f.coef2)) {
                if (has_terms) {
                    printf(" %c ", f.coef2 > 0 ? '+' : '-');
                } else if (f.coef2 < 0) {
                    printf("-");
                }
                print_term(fabs(f.coef2), f.r2, 0);
                has_terms = 1;
            }
            
            if (!has_terms) {
                printf("0");
            }
            printf("\n");
            break;
        }
            
        case 2: {
            printf("x_n = ");
            printf("(");
            
            int has_terms = 0;
            if (!is_zero(f.coef1)) {
                printf("%.6f", f.coef1);
                has_terms = 1;
            }
            
            if (!is_zero(f.coef2)) {
                if (has_terms) {
                    printf(" + ");
                }
                printf("%.6f*(n-1)", f.coef2);
                has_terms = 1;
            }
            
            if (!has_terms) {
                printf("0");
            }
            printf(")");
            
            print_power(f.r1);
            printf("\n");
            break;
        }
            
        case 3: {
            // Комплексные корни
            printf("x_n = ");
            
            if (fabs(f.modulus - 1.0) > DBL_EPSILON) {
                printf("%.6f^(n-1)", f.modulus);
            }
            
            // Трига
            printf(" * [");
            
            int has_terms = 0;
            if (!is_zero(f.coef1)) {
                printf("%.6f * cos((n-1)*%.6f)", f.coef1, f.theta);
                has_terms = 1;
            }
            
            if (!is_zero(f.coef2)) {
                if (has_terms) {
                    printf(" %c ", f.coef2 > 0 ? '+' : '-');
                } else if (f.coef2 < 0) {
                    printf("-");
                }
                printf("%.6f * sin((n-1)*%.6f)", fabs(f.coef2), f.theta);
                has_terms = 1;
            }
            
            if (!has_terms) {
                printf("0");
            }
            printf("]");
            
            if (fabs(f.modulus - 1.0) < DBL_EPSILON && has_terms) {
                printf("  [where modulus = 1]");
            }
            printf("\n");
            break;
        }
            
        default:
            printf("Unknown case type: %d\n", f.case_type);
    }
}

// Вспомогательные 
static int is_zero(double x) {
    return fabs(x) < DBL_EPSILON;
}

static void print_term(double coef, double base, int is_first) {
    if (is_zero(coef)) return;
    
    if (!is_first) {
        printf(coef > 0 ? "+ " : "- ");
    } else if (coef < 0) {
        printf("-");
    }
    
    double abs_coef = fabs(coef);
    if (fabs(abs_coef - 1.0) > DBL_EPSILON) {
        printf("%.6f", abs_coef);
    }
    
    if (fabs(abs_coef - 1.0) > DBL_EPSILON && 
        fabs(base - 1.0) > DBL_EPSILON && fabs(base + 1.0) > DBL_EPSILON) {
        printf(" * ");
    }
    
    print_power(base);
}

static void print_power(double base) {
    if (is_zero(base)) {
        printf("0^(n-1)");
    } else if (fabs(base - 1.0) < DBL_EPSILON) {
        printf("1^(n-1)");
    } else if (fabs(base + 1.0) < DBL_EPSILON) {
        printf("(-1)^(n-1)");
    } else {
        printf("%.6f^(n-1)", base);
    }
}
