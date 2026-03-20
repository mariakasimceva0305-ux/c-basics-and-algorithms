#ifndef LRPS_H
#define LRPS_H

typedef struct {
    int case_type;
    double r1, r2;
    double coef1, coef2;
} Formula;

Formula find_formula(int a, int b, int c, int d);
void show_formula(Formula f);

#endif