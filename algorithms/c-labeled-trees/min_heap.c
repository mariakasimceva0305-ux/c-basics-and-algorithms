#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void free_min_heap(MinHeap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void insert_min_heap(MinHeap* heap, int value) {
    if (heap->size >= heap->capacity) return;
    
    heap->data[heap->size] = value;
    int i = heap->size;
    heap->size++;
    
    while (i > 0 && heap->data[(i-1)/2] > heap->data[i]) {
        int temp = heap->data[(i-1)/2];
        heap->data[(i-1)/2] = heap->data[i];
        heap->data[i] = temp;
        i = (i-1)/2;
    }
}

int extract_min(MinHeap* heap) {
    if (heap->size == 0) return -1;
    
    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->size--;
    
    int i = 0;
    while (2*i+1 < heap->size) {
        int left = 2*i+1;
        int right = 2*i+2;
        int smallest = left;
        
        if (right < heap->size && heap->data[right] < heap->data[left]) {
            smallest = right;
        }
        
        if (heap->data[i] <= heap->data[smallest]) break;
        
        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        
        i = smallest;
    }
    
    return min;
}