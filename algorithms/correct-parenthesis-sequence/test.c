#include "../include/cbs.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Проверка правильности скобочной последовательности
static int is_valid_sequence(const char *seq, unsigned n) {
    int balance = 0;
    for (unsigned i = 0; i < 2*n; i++) {
        if (seq[i] == '(') balance++;
        else balance--;
        if (balance < 0) return 0;
    }
    return balance == 0;
}

// Тест чисел Каталана
static void test_catalan_numbers() {
    unsigned catalan[] = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 58786};
    
    for (unsigned n = 0; n <= 5; n++) {
        iterator_t it;
        iterator_init(&it, n);
        
        unsigned count = 0;
        do {
            assert(is_valid_sequence(iterator_value(&it)->sequence, n));
            count++;
            iterator_next(&it);
        } while (iterator_has_next(&it));
        
        printf("n = %u: %u sequences (expected %u)\n", n, count, catalan[n]);
        assert(count == catalan[n]);
        iterator_destroy(&it);
    }
}

// Тест уникальности последовательностей
static void test_uniqueness(unsigned n) {
    iterator_t it;
    iterator_init(&it, n);
    
    unsigned capacity = 1000;
    unsigned count = 0;
    char **sequences = (char**)malloc(capacity * sizeof(char*));
    
    do {
        if (count >= capacity) {
            capacity *= 2;
            sequences = (char**)realloc(sequences, capacity * sizeof(char*));
        }
        sequences[count] = strdup(iterator_value(&it)->sequence);
        count++;
        iterator_next(&it);
    } while (iterator_has_next(&it));
    
    // Проверка на дубликаты
    for (unsigned i = 0; i < count; i++) {
        for (unsigned j = i + 1; j < count; j++) {
            if (strcmp(sequences[i], sequences[j]) == 0) {
                printf("Duplicate found: %s\n", sequences[i]);
                assert(0);
            }
        }
    }
    
    // Очистка
    for (unsigned i = 0; i < count; i++) {
        free(sequences[i]);
    }
    free(sequences);
    iterator_destroy(&it);
}

// Тест граничных значений
static void test_edge_cases() {
    // n = 0
    iterator_t it;
    iterator_init(&it, 0);
    assert(strcmp(iterator_value(&it)->sequence, "") == 0);
    assert(!iterator_has_next(&it));
    iterator_destroy(&it);

    // n = 1
    iterator_init(&it, 1);
    assert(strcmp(iterator_value(&it)->sequence, "()") == 0);
    assert(!iterator_has_next(&it));
    iterator_destroy(&it);
}

// Тест порядка последовательностей
static void test_sequence_order() {
    // Для n=3 проверяем известные последовательности в правильном порядке
    const char *expected[] = {"((()))", "(()())", "(())()", "()(())", "()()()"};
    
    iterator_t it;
    iterator_init(&it, 3);
    
    for (int i = 0; i < 5; i++) {
        assert(strcmp(iterator_value(&it)->sequence, expected[i]) == 0);
        if (i < 4) assert(iterator_has_next(&it));
        iterator_next(&it);
    }
    assert(!iterator_has_next(&it));
    iterator_destroy(&it);
}

// Тест на утечки памяти
static void test_memory_leaks() {
    for (unsigned n = 0; n <= 10; n++) {
        iterator_t it;
        iterator_init(&it, n);
        
        while (iterator_has_next(&it)) {
            iterator_next(&it);
        }
        
        iterator_destroy(&it);
    }
}

int main() {
    printf("Testing edge cases...\n");
    test_edge_cases();
    
    printf("Testing sequence order...\n");
    test_sequence_order();
    
    printf("Testing uniqueness...\n");
    for (unsigned n = 0; n <= 5; n++) {
        test_uniqueness(n);
    }
    
    printf("Testing Catalan numbers...\n");
    test_catalan_numbers();
    
    printf("Testing memory leaks...\n");
    test_memory_leaks();
    
    printf("All tests passed!\n");
    return 0;
}
