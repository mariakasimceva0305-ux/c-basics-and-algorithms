#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} vector_t;

typedef struct {
    size_t n;
    int* removed;
    vector_t* adj;
    int* degree;
} graph_t;

void vector_init(vector_t* vec);
void vector_push_back(vector_t* vec, int value);
void vector_remove_all(vector_t* vec, int value);
int vector_contains(vector_t* vec, int value);
size_t vector_count(const vector_t* vec, int value);
void vector_free(vector_t* vec);

void graph_init(graph_t* g, size_t n);
void graph_add_edge(graph_t* g, int u, int v);
void graph_remove_edge(graph_t* g, int u, int v);
int graph_has_edge(graph_t* g, int u, int v);
void graph_free(graph_t* g);
void simplify_graph(graph_t* g);

void* xmalloc(size_t size);
void* xcalloc(size_t count, size_t size);
void* xrealloc(void* ptr, size_t size);

#endif