#ifndef CBS_H
#define CBS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct CBS {
    unsigned n;
    char *sequence;
} cbs_t;

typedef struct ObsIterator {
    cbs_t value;
    int has_next;
    unsigned n;
} iterator_t;

void iterator_init(iterator_t *i, unsigned n);
const cbs_t *iterator_value(const iterator_t *i);
int iterator_has_next(const iterator_t *i);
void iterator_next(iterator_t *i);
void iterator_destroy(iterator_t *i);

#endif
