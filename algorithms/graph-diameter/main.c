#include <stdio.h>
#include <stdlib.h>
#include "../include/graph_utils.h"

int main() {
    int n, m;
    printf("Enter vertex count and edge count: ");
    scanf("%d %d", &n, &m);
    
    GraphStruct* graph = create_graph(n);
    
    printf("Enter %d edges (vertices from 0 to %d):\n", m, n-1);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge_connection(graph, u, v);
    }
    
    int diameter = find_graph_diameter(graph);
    printf("Graph diameter: %d\n", diameter);
    
    free_graph_memory(graph);
    return 0;
}