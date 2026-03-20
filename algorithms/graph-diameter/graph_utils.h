#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <stddef.h>

typedef struct {
    int** adjacency_list;
    int* neighbor_count;
    int* memory_size;
    int vertex_count;
    int edge_count;
} GraphStruct;

typedef struct {
    int* distances;
    int max_distance;
    int farthest_vertex;
    int visited_count;
} DistanceResult;

GraphStruct* create_graph(int vertex_count);
void add_edge_connection(GraphStruct* graph, int u, int v);
void free_graph_memory(GraphStruct* graph);
DistanceResult* compute_distances_from_vertex(GraphStruct* graph, int start_vertex);
int find_graph_diameter(GraphStruct* graph);

#endif