#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

Node* create_node(int vertex) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = create_node(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

int validate_prufer_code(int n, int* prufer, int prufer_len) {
    if (n <= 0) return 0;
    if (n == 1) return (prufer_len == 0);
    if (prufer_len != n - 2) return 0;
    
    for (int i = 0; i < prufer_len; i++) {
        if (prufer[i] < 1 || prufer[i] > n) {
            return 0;
        }
    }
    return 1;
}

Graph* prufer_to_tree(int n, int* prufer, int prufer_len) {
    if (!validate_prufer_code(n, prufer, prufer_len)) {
        return NULL;
    }
    
    if (n == 1) {
        Graph* graph = (Graph*)malloc(sizeof(Graph));
        graph->n = 1;
        graph->adj_list = (Node**)calloc(2, sizeof(Node*)); // 0-indexed, we use 1..n
        return graph;
    }
    
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adj_list = (Node**)calloc(n + 1, sizeof(Node*));
    
    int* degree = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        degree[i] = 1;
    }
    
    for (int i = 0; i < prufer_len; i++) {
        degree[prufer[i]]++;
    }
    
    // Optimized O(n) algorithm
    int ptr = 1;
    while (ptr <= n && degree[ptr] != 1) {
        ptr++;
    }
    
    int leaf = ptr;
    
    for (int i = 0; i < prufer_len; i++) {
        int p = prufer[i];
        
        add_edge(graph, leaf, p);
        degree[leaf]--;
        degree[p]--;
        
        if (degree[p] == 1 && p < ptr) {
            leaf = p;
        } else {
            ptr++;
            while (ptr <= n && degree[ptr] != 1) {
                ptr++;
            }
            leaf = ptr;
        }
    }
    
    // Add last edge
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            for (int j = i + 1; j <= n; j++) {
                if (degree[j] == 1) {
                    add_edge(graph, i, j);
                    break;
                }
            }
            break;
        }
    }
    
    free(degree);
    return graph;
}

void free_graph(Graph* graph) {
    if (!graph) return;
    
    for (int i = 1; i <= graph->n; i++) {
        Node* current = graph->adj_list[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);
}

void print_adjacency_list(Graph* graph) {
    for (int i = 1; i <= graph->n; i++) {
        printf("%d: ", i);
        Node* current = graph->adj_list[i];
        while (current) {
            printf("%d", current->vertex);
            if (current->next) printf(" ");
            current = current->next;
        }
        printf("\n");
    }
}