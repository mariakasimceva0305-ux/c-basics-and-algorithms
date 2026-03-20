#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

void* xmalloc(size_t size) {
    if (size == 0) return NULL;
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* xcalloc(size_t count, size_t size) {
    if (count == 0 || size == 0) return NULL;
    void* ptr = calloc(count, size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* xrealloc(void* ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void vector_init(vector_t* vec) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

void vector_push_back(vector_t* vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity = (vec->capacity == 0) ? 8 : vec->capacity * 2;
        vec->data = xrealloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size++] = value;
}

void vector_remove_all(vector_t* vec, int value) {
    size_t write_index = 0;
    for (size_t i = 0; i < vec->size; i++) {
        if (vec->data[i] != value) {
            vec->data[write_index++] = vec->data[i];
        }
    }
    vec->size = write_index;
}

int vector_contains(vector_t* vec, int value) {
    for (size_t i = 0; i < vec->size; i++) {
        if (vec->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

size_t vector_count(const vector_t* vec, int value) {
    size_t count = 0;
    for (size_t i = 0; i < vec->size; i++) {
        if (vec->data[i] == value) {
            count++;
        }
    }
    return count;
}

void vector_free(vector_t* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = vec->capacity = 0;
}

void graph_init(graph_t* g, size_t n) {
    g->n = n;
    g->removed = xcalloc(n, sizeof(int));
    g->degree = xcalloc(n, sizeof(int));
    g->adj = xmalloc(n * sizeof(vector_t));
    
    for (size_t i = 0; i < n; i++) {
        vector_init(&g->adj[i]);
    }
}

void graph_add_edge(graph_t* g, int u, int v) {
    if (u < 0 || v < 0 || (size_t)u >= g->n || (size_t)v >= g->n) {
        return;
    }
    if (u == v) {
        return;
    }
    if (g->removed[u] || g->removed[v]) {
        return;
    }
    
    vector_push_back(&g->adj[u], v);
    vector_push_back(&g->adj[v], u);
    
    g->degree[u] = g->adj[u].size;
    g->degree[v] = g->adj[v].size;
}

void graph_remove_edge(graph_t* g, int u, int v) {
    if (u < 0 || v < 0 || (size_t)u >= g->n || (size_t)v >= g->n) {
        return;
    }
    
    vector_remove_all(&g->adj[u], v);
    vector_remove_all(&g->adj[v], u);
    
    g->degree[u] = g->adj[u].size;
    g->degree[v] = g->adj[v].size;
}

int graph_has_edge(graph_t* g, int u, int v) {
    if (u < 0 || v < 0 || (size_t)u >= g->n || (size_t)v >= g->n) {
        return 0;
    }
    return vector_contains(&g->adj[u], v);
}

void graph_free(graph_t* g) {
    free(g->removed);
    free(g->degree);
    
    for (size_t i = 0; i < g->n; i++) {
        vector_free(&g->adj[i]);
    }
    free(g->adj);
}

void simplify_graph(graph_t* g) {
    if (g->n == 0) return;
    
    int* queue = xmalloc(g->n * sizeof(int));
    int* in_queue = xcalloc(g->n, sizeof(int));
    int queue_start = 0, queue_end = 0;
    size_t queue_capacity = g->n;
    
    for (size_t i = 0; i < g->n; i++) {
        if (!g->removed[i] && g->degree[i] == 2) {
            if (queue_end >= (int)queue_capacity) {
                queue_capacity *= 2;
                queue = xrealloc(queue, queue_capacity * sizeof(int));
                in_queue = xrealloc(in_queue, queue_capacity * sizeof(int));
            }
            queue[queue_end] = i;
            in_queue[i] = 1;
            queue_end++;
        }
    }
    
    while (queue_start < queue_end) {
        int v = queue[queue_start++];
        in_queue[v] = 0;
        
        if (g->removed[v] || g->degree[v] != 2) {
            continue;
        }
        
        if (g->adj[v].size < 2) {
            continue;
        }
        
        int u = -1, w = -1;
        for (size_t i = 0; i < g->adj[v].size && (u == -1 || w == -1); i++) {
            int neighbor = g->adj[v].data[i];
            if (!g->removed[neighbor]) {
                if (u == -1) {
                    u = neighbor;
                } else if (neighbor != u) {
                    w = neighbor;
                }
            }
        }
        
        if (u == -1 || w == -1 || u == w) {
            continue;
        }
        
        g->removed[v] = 1;
        
        graph_remove_edge(g, u, v);
        graph_remove_edge(g, w, v);
        
        graph_add_edge(g, u, w);
        
        if (!g->removed[u] && g->degree[u] == 2 && !in_queue[u]) {
            if (queue_end >= (int)queue_capacity) {
                queue_capacity *= 2;
                queue = xrealloc(queue, queue_capacity * sizeof(int));
                in_queue = xrealloc(in_queue, queue_capacity * sizeof(int));
            }
            queue[queue_end] = u;
            in_queue[u] = 1;
            queue_end++;
        }
        
        if (!g->removed[w] && g->degree[w] == 2 && !in_queue[w]) {
            if (queue_end >= (int)queue_capacity) {
                queue_capacity *= 2;
                queue = xrealloc(queue, queue_capacity * sizeof(int));
                in_queue = xrealloc(in_queue, queue_capacity * sizeof(int));
            }
            queue[queue_end] = w;
            in_queue[w] = 1;
            queue_end++;
        }
    }
    
    free(queue);
    free(in_queue);
}