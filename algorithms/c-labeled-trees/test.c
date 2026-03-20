#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/graph.h"

void test_empty_tree() {
    printf("Testing empty tree (n=1)...\n");
    Graph* graph = prufer_to_tree(1, NULL, 0);
    assert(graph != NULL);
    assert(graph->n == 1);
    assert(graph->adj_list[1] == NULL);
    free_graph(graph);
    printf("Passed!\n");
}

void test_two_vertices() {
    printf("Testing two vertices...\n");
    int prufer[] = {};
    Graph* graph = prufer_to_tree(2, prufer, 0);
    assert(graph != NULL);
    assert(graph->n == 2);
    
    assert(graph->adj_list[1] != NULL);
    assert(graph->adj_list[1]->vertex == 2);
    assert(graph->adj_list[2] != NULL);
    assert(graph->adj_list[2]->vertex == 1);
    
    free_graph(graph);
    printf("Passed!\n");
}

void test_three_vertices() {
    printf("Testing three vertices...\n");
    int prufer[] = {3};
    Graph* graph = prufer_to_tree(3, prufer, 1);
    assert(graph != NULL);
    assert(graph->n == 3);
    
    Node* node = graph->adj_list[3];
    int count = 0;
    while (node) {
        count++;
        node = node->next;
    }
    assert(count == 2);
    
    free_graph(graph);
    printf("Passed!\n");
}

void test_example_from_task() {
    printf("Testing example from task...\n");
    int prufer[] = {2, 2, 3};
    Graph* graph = prufer_to_tree(5, prufer, 3);
    assert(graph != NULL);
    assert(graph->n == 5);
    
    for (int i = 1; i <= 5; i++) {
        assert(graph->adj_list[i] != NULL);
    }
    
    free_graph(graph);
    printf("Passed!\n");
}

void test_larger_tree() {
    printf("Testing larger tree...\n");
    int prufer[] = {4, 4, 4, 5};
    Graph* graph = prufer_to_tree(6, prufer, 4);
    assert(graph != NULL);
    assert(graph->n == 6);
    
    free_graph(graph);
    printf("Passed!\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    Graph* graph = prufer_to_tree(0, NULL, 0);
    assert(graph == NULL);
    
    int invalid_prufer[] = {7, 8};
    graph = prufer_to_tree(3, invalid_prufer, 2);
    
    printf("Passed!\n");
}

void test_memory_management() {
    printf("Testing memory management...\n");
    
    for (int i = 0; i < 100; i++) {
        int prufer[] = {2, 3};
        Graph* graph = prufer_to_tree(4, prufer, 2);
        assert(graph != NULL);
        free_graph(graph);
    }
    
    printf("Passed!\n");
}

int main() {
    printf("Starting tests...\n\n");
    
    test_empty_tree();
    test_two_vertices();
    test_three_vertices();
    test_example_from_task();
    test_larger_tree();
    test_edge_cases();
    test_memory_management();
    
    printf("\nAll tests passed! ✓\n");
    return 0;
}