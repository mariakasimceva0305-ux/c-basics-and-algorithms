#include "../include/sat_solver.h"
#include <stdlib.h>
#include <stddef.h>

int get_literal_value(int literal, int* assignment, int max_var) {
    if (literal == 0) return 1; // Всегда истинен
    
    int var_index = (literal > 0) ? literal : -literal;
    if (var_index < 1 || var_index > max_var) return 0; // Не существует
    
    int value = assignment[var_index];
    return (literal > 0) ? value : !value;
}

int is_clause_satisfied(clause_t clause, int* assignment, int max_var) {
    int val_i = get_literal_value(clause.i, assignment, max_var);
    int val_j = get_literal_value(clause.j, assignment, max_var);
    int val_k = get_literal_value(clause.k, assignment, max_var);
    
    return val_i || val_j || val_k;
}

int try_assignments(int* assignment, int current_var, int max_var, 
                   const clause_t *clauses, unsigned size) {
    if (current_var > max_var) {
        for (unsigned i = 0; i < size; i++) {
            if (!is_clause_satisfied(clauses[i], assignment, max_var)) {
                return 0;
            }
        }
        return 1;
    }
    
    assignment[current_var] = 1;
    if (try_assignments(assignment, current_var + 1, max_var, clauses, size)) {
        return 1;
    }
    
    assignment[current_var] = 0;
    return try_assignments(assignment, current_var + 1, max_var, clauses, size);
}

int is_sat(const clause_t *clauses, unsigned size) {
    if (clauses == NULL) return (size == 0) ? 1 : 0;
    if (size == 0) return 1;
    
    // Максимальная переменная
    int max_var = 0;
    int has_any_non_zero_literal = 0;
    
    for (unsigned i = 0; i < size; i++) {
        clause_t c = clauses[i];
        
        if (c.i != 0) { 
            int var = (c.i > 0) ? c.i : -c.i;
            if (var > max_var) max_var = var;
            has_any_non_zero_literal = 1;
        }
        if (c.j != 0) { 
            int var = (c.j > 0) ? c.j : -c.j;
            if (var > max_var) max_var = var;
            has_any_non_zero_literal = 1;
        }
        if (c.k != 0) { 
            int var = (c.k > 0) ? c.k : -c.k;
            if (var > max_var) max_var = var;
            has_any_non_zero_literal = 1;
        }
    }
    
    //
    if (!has_any_non_zero_literal) return 1;
    
    // 
    if (max_var == 0) {
        return 0;
    }
    
    // перебор
    int* assignment = (int*)calloc(max_var + 1, sizeof(int));
    if (assignment == NULL) return 0;
    
    int result = try_assignments(assignment, 1, max_var, clauses, size);
    free(assignment);
    return result;
}
