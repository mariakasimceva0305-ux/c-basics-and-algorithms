#ifndef SAT_SOLVER_H
#define SAT_SOLVER_H

typedef struct Clause {
    int i, j, k;
} clause_t;

int is_sat(const clause_t *clauses, unsigned size);

#endif