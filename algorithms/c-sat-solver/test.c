#include <stdio.h>
#include <windows.h> 
#include "../include/sat_solver.h"

void test_case(const char* name, int expected, int actual) {
    printf("%s: %s\n", name, (expected == actual) ? "PASS" : "FAIL");
    if (expected != actual) {
        printf("  Expected: %d, Got: %d\n", expected, actual);
    }
}

int main() {
    SetConsoleOutputCP(65001);
    printf("ТЕСТИРОВАНИЕ\n\n");
    
    // 1. База
    printf("1. Базовые случаи:\n");
    test_case("NULL с size=0", 1, is_sat(NULL, 0));
    test_case("NULL с size>0", 0, is_sat(NULL, 5));
    
    clause_t empty[0];
    test_case("Пустой массив", 1, is_sat(empty, 0));
    
    // 2. Все нулевые индексы
    printf("\n2. Все нулевые индексы:\n");
    clause_t zeros1[] = {{0,0,0}};
    test_case("Одна клауза с нулями", 1, is_sat(zeros1, 1));
    
    clause_t zeros2[] = {{0,0,0}, {0,0,0}, {0,0,0}};
    test_case("Много клауз с нулями", 1, is_sat(zeros2, 3));
    
    // 3. Смешанные случаи
    printf("\n3. Смешанные случаи:\n");
    clause_t mixed1[] = {{0,2,3}, {1,0,-2}};
    test_case("Смешанные в разных клаузах", 1, is_sat(mixed1, 2));
    
    // 4. Простые выполнимые формулы
    printf("\n4. Простые выполнимые:\n");
    clause_t simple1[] = {{1,2,3}};
    test_case("Одна клауза", 1, is_sat(simple1, 1));
    
    clause_t simple2[] = {{1,-1,2}};
    test_case("Тривиально выполнимая", 1, is_sat(simple2, 1));
    
    // 5. Простые невыполнимые формулы
    printf("\n5. Простые невыполнимые:\n");
    clause_t unsat1[] = {{1,1,1}, {-1,-1,-1}};
    test_case("Противоречие n=1", 0, is_sat(unsat1, 2));
    
    // 6. Граничные значения n
    printf("\n6. Граничные значения n:\n");
    clause_t n1[] = {{1,1,1}};
    test_case("n=1 выполнимая", 1, is_sat(n1, 1));
    
    clause_t n30[] = {{30,30,30}};
    test_case("n=30 выполнимая", 1, is_sat(n30, 1));
    
    clause_t n31[] = {{31,31,31}};
    test_case("n=31 (превышение)", 0, is_sat(n31, 1));
    
    // 7. Отрицательные индексы
    printf("\n7. Отрицательные индексы:\n");
    clause_t neg1[] = {{-1,-2,3}};
    test_case("Отрицательные", 1, is_sat(neg1, 1));
    
    printf("\nТЕСТИРОВАНИЕ ЗАВЕРШЕНО\n");
    return 0;
}