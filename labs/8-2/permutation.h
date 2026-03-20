#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <stddef.h>

void permutation_init(unsigned int seed);

int* generate_permutation(int n);

void free_permutation(int* perm);

#endif