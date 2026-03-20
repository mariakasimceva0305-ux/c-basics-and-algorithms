#include "../include/graph_utils.h"
#include <stdio.h>
#include <assert.h>

void test_empty_graph() {
    printf("Test 1: Empty graph\n");
    GraphStruct* g = create_graph(0);
    int d = find_graph_diameter(g);
    assert(d == 0);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_single_vertex() {
    printf("Test 2: Single vertex\n");
    GraphStruct* g = create_graph(1);
    int d = find_graph_diameter(g);
    assert(d == 0);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_two_vertices_with_edge() {
    printf("Test 3: Two vertices with edge\n");
    GraphStruct* g = create_graph(2);
    add_edge_connection(g, 0, 1);
    int d = find_graph_diameter(g);
    assert(d == 1);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_two_vertices_no_edge() {
    printf("Test 4: Two vertices without edge\n");
    GraphStruct* g = create_graph(2);
    int d = find_graph_diameter(g);
    assert(d == 0);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_simple_connected_graph() {
    printf("Test 5: Simple connected graph\n");
    GraphStruct* g = create_graph(5);
    add_edge_connection(g, 0, 1);
    add_edge_connection(g, 1, 2);
    add_edge_connection(g, 2, 3);
    add_edge_connection(g, 3, 4);
    int d = find_graph_diameter(g);
    assert(d == 4);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_complete_graph_K4() {
    printf("Test 6: Complete graph K4\n");
    GraphStruct* g = create_graph(4);
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            add_edge_connection(g, i, j);
        }
    }
    int d = find_graph_diameter(g);
    assert(d == 1);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

void test_disconnected_graph() {
    printf("Test 7: Disconnected graph\n");
    GraphStruct* g = create_graph(6);
    add_edge_connection(g, 0, 1);
    add_edge_connection(g, 1, 2);
    add_edge_connection(g, 3, 4);
    add_edge_connection(g, 4, 5);
    int d = find_graph_diameter(g);
    assert(d == 2);
    free_graph_memory(g);
    printf("Passed!\n\n");
}

int main() {
    printf("Running tests \n\n");
    
    test_empty_graph();
    test_single_vertex();
    test_two_vertices_with_edge();
    test_two_vertices_no_edge();
    test_simple_connected_graph();
    test_complete_graph_K4();
    test_disconnected_graph();
    
    printf("ALL TESTS PASSED\n");
    return 0;
}