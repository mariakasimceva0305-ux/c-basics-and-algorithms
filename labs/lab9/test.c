#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

void test_empty_graph() {
    graph_t g;
    graph_init(&g, 0);
    simplify_graph(&g);
    graph_free(&g);
    printf("Empty graph test passed\n");
}

void test_single_vertex() {
    graph_t g;
    graph_init(&g, 1);
    simplify_graph(&g);
    assert(!g.removed[0]);
    graph_free(&g);
    printf("Single vertex test passed\n");
}

void test_two_vertices() {
    graph_t g;
    graph_init(&g, 2);
    graph_add_edge(&g, 0, 1);
    simplify_graph(&g);
    assert(!g.removed[0] && !g.removed[1]);
    assert(g.degree[0] == 1 && g.degree[1] == 1);
    graph_free(&g);
    printf("Two vertices test passed\n");
}

void test_three_vertex_chain() {
    graph_t g;
    graph_init(&g, 3);
    graph_add_edge(&g, 0, 1);
    graph_add_edge(&g, 1, 2);
    
    simplify_graph(&g);
    
    assert(g.removed[1]);
    assert(!g.removed[0] && !g.removed[2]);
    assert(g.adj[0].size == 1 && g.adj[2].size == 1);
    assert(g.adj[0].data[0] == 2);
    assert(g.adj[2].data[0] == 0);
    
    graph_free(&g);
    printf("Three vertex chain test passed\n");
}

void test_multiple_edges_to_same_vertex() {
    graph_t g;
    graph_init(&g, 3);
    graph_add_edge(&g, 0, 1);
    graph_add_edge(&g, 0, 1);
    graph_add_edge(&g, 1, 2);
    
    simplify_graph(&g);
    
    assert(!g.removed[1]);
    assert(g.degree[1] == 3);
    graph_free(&g);
    printf("Multiple edges to same vertex test passed\n");
}

void test_large_chain() {
    graph_t g;
    const int N = 10;
    graph_init(&g, N);
    
    for (int i = 0; i < N - 1; i++) {
        graph_add_edge(&g, i, i + 1);
    }
    
    simplify_graph(&g);
    
    assert(!g.removed[0] && !g.removed[N - 1]);
    for (int i = 1; i < N - 1; i++) {
        assert(g.removed[i]);
    }
    graph_free(&g);
    printf("Large chain test passed\n");
}

void test_star_graph() {
    graph_t g;
    graph_init(&g, 5);
    graph_add_edge(&g, 0, 1);
    graph_add_edge(&g, 0, 2);
    graph_add_edge(&g, 0, 3);
    graph_add_edge(&g, 0, 4);
    
    simplify_graph(&g);
    
    for (int i = 0; i < 5; i++) {
        assert(!g.removed[i]);
    }
    graph_free(&g);
    printf("Star graph test passed\n");
}

int main() {
    
    test_empty_graph();
    test_single_vertex();
    test_two_vertices();
    test_three_vertex_chain();
    test_multiple_edges_to_same_vertex();
    test_large_chain();
    test_star_graph();
    
    printf("\nAll tests passed!\n");
    return 0;
}