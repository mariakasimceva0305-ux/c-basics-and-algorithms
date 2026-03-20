#include "cbs.h"

static int next_sequence(char *seq, unsigned n) {
    int depth = 0;
    for (int i = 2*n - 1; i >= 0; i--) {
        if (seq[i] == '(') {
            depth--;
        } else {
            depth++;
        }
        
        if (seq[i] == '(' && depth > 0) {
            seq[i] = ')';
            
            int open_count = (2*n - i - 1 - depth) / 2;
            int close_count = 2*n - i - 1 - open_count;
            
            for (int j = i + 1; j < i + 1 + open_count; j++) {
                seq[j] = '(';
            }
            for (int j = i + 1 + open_count; j < 2*n; j++) {
                seq[j] = ')';
            }
            return 1;
        }
    }
    return 0;
}

void iterator_init(iterator_t *i, unsigned n) {
    i->n = n;
    i->value.n = n;
    i->value.sequence = (char*)malloc(2*n + 1);
    
    if (n > 0) {
        for (unsigned j = 0; j < n; j++) {
            i->value.sequence[j] = '(';
            i->value.sequence[j + n] = ')';
        }
        i->has_next = 1;
    } else {
        i->value.sequence[0] = '\0';
        i->has_next = 0;
    }
    i->value.sequence[2*n] = '\0';
}

const cbs_t *iterator_value(const iterator_t *i) {
    return &i->value;
}

int iterator_has_next(const iterator_t *i) {
    return i->has_next;
}

void iterator_next(iterator_t *i) {
    if (!i->has_next) return;
    
    i->has_next = next_sequence(i->value.sequence, i->n);
}

void iterator_destroy(iterator_t *i) {
    free(i->value.sequence);
    i->value.sequence = NULL;
}
