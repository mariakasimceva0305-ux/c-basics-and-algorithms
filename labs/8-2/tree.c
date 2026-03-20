#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

static MinHeap* heap_create(int capacity) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void heap_free(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

static void heap_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;
    if (smallest != i) {
        heap_swap(&heap->data[i], &heap->data[smallest]);
        heap_heapify(heap, smallest);
    }
}

static void heap_insert(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) return;
    
    heap->data[heap->size] = value;
    int i = heap->size;
    heap->size++;
    
    while (i > 0 && heap->data[(i-1)/2] > heap->data[i]) {
        heap_swap(&heap->data[i], &heap->data[(i-1)/2]);
        i = (i-1)/2;
    }
}

static int heap_extract_min(MinHeap* heap) {
    if (heap->size == 0) return -1;
    
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heap_heapify(heap, 0);
    
    return min;
}

static void add_edge(Tree* tree, int u, int v) {
    TreeNode* new_node_u = malloc(sizeof(TreeNode));
    new_node_u->vertex = v;
    new_node_u->next = tree->adjacency_list[u];
    tree->adjacency_list[u] = new_node_u;

    TreeNode* new_node_v = malloc(sizeof(TreeNode));
    new_node_v->vertex = u;
    new_node_v->next = tree->adjacency_list[v];
    tree->adjacency_list[v] = new_node_v;
}

Tree* prufer_to_tree(const int* prufer, int n) {
    if (n < 0) return NULL;
    
    Tree* tree = malloc(sizeof(Tree));
    tree->n = n;
    tree->adjacency_list = calloc(n + 1, sizeof(TreeNode*));
    
    if (n == 0) {
        return tree;
    }
    
    if (n == 1) {
        return tree;
    }

    int* degree = calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        degree[i] = 1;
    }
    
    if (prufer != NULL) {
        for (int i = 0; i < n - 2; i++) {
            degree[prufer[i]]++;
        }
    }

    MinHeap* heap = heap_create(n);
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            heap_insert(heap, i);
        }
    }

    if (prufer != NULL) {
        for (int i = 0; i < n - 2; i++) {
            int u = heap_extract_min(heap);
            int p = prufer[i];
            add_edge(tree, u, p);
            degree[u]--;
            degree[p]--;
            if (degree[p] == 1) {
                heap_insert(heap, p);
            }
        }
    }

    int u = heap_extract_min(heap);
    int v = heap_extract_min(heap);
    add_edge(tree, u, v);

    free(degree);
    heap_free(heap);
    return tree;
}

Tree* generate_random_tree(int n) {
    if (n < 0) return NULL;
    
    if (n <= 2) {
        return prufer_to_tree(NULL, n);
    }

    int len = n - 2;
    int* prufer = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        prufer[i] = rand() % n + 1;
    }

    Tree* tree = prufer_to_tree(prufer, n);
    free(prufer);
    return tree;
}

void free_tree(Tree* tree) {
    if (tree == NULL) return;
    
    if (tree->adjacency_list != NULL) {
        for (int i = 0; i <= tree->n; i++) {
            TreeNode* current = tree->adjacency_list[i];
            while (current != NULL) {
                TreeNode* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(tree->adjacency_list);
    }
    free(tree);
}