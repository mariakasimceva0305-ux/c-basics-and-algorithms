#include "graph_utils.h"
#include <stdlib.h>
#include <limits.h>

#define INITIAL_CAPACITY 4

GraphStruct* create_graph(int vertex_count) {
    GraphStruct* graph = (GraphStruct*)malloc(sizeof(GraphStruct));
    graph->vertex_count = vertex_count;
    graph->edge_count = 0;
    
    graph->adjacency_list = (int**)malloc(vertex_count * sizeof(int*));
    graph->neighbor_count = (int*)calloc(vertex_count, sizeof(int));
    graph->memory_size = (int*)malloc(vertex_count * sizeof(int));
    
    for (int i = 0; i < vertex_count; i++) {
        graph->memory_size[i] = INITIAL_CAPACITY;
        graph->adjacency_list[i] = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    }
    
    return graph;
}

void add_edge_connection(GraphStruct* graph, int u, int v) {
    if (u < 0 || u >= graph->vertex_count || v < 0 || v >= graph->vertex_count) {
        return;
    }
    
    if (graph->neighbor_count[u] >= graph->memory_size[u]) {
        graph->memory_size[u] *= 2;
        graph->adjacency_list[u] = (int*)realloc(graph->adjacency_list[u], 
                                               graph->memory_size[u] * sizeof(int));
    }
    graph->adjacency_list[u][graph->neighbor_count[u]++] = v;
    
    // 
    if (graph->neighbor_count[v] >= graph->memory_size[v]) {
        graph->memory_size[v] *= 2;
        graph->adjacency_list[v] = (int*)realloc(graph->adjacency_list[v], 
                                               graph->memory_size[v] * sizeof(int));
    }
    graph->adjacency_list[v][graph->neighbor_count[v]++] = u;
    
    graph->edge_count++;
}

void free_graph_memory(GraphStruct* graph) {
    if (graph == NULL) return;
    
    for (int i = 0; i < graph->vertex_count; i++) {
        free(graph->adjacency_list[i]);
    }
    free(graph->adjacency_list);
    free(graph->neighbor_count);
    free(graph->memory_size);
    free(graph);
}

DistanceResult* compute_distances_from_vertex(GraphStruct* graph, int start_vertex) {
    if (graph == NULL || start_vertex < 0 || start_vertex >= graph->vertex_count) {
        return NULL;
    }
    
    DistanceResult* result = (DistanceResult*)malloc(sizeof(DistanceResult));
    result->distances = (int*)malloc(graph->vertex_count * sizeof(int));
    result->max_distance = -1;
    result->farthest_vertex = start_vertex;
    result->visited_count = 0;
    
    //-1 непосещенные
    for (int i = 0; i < graph->vertex_count; i++) {
        result->distances[i] = -1;
    }
    
    // BFS
    int* queue = (int*)malloc(graph->vertex_count * sizeof(int));
    int front = 0, rear = 0;
    
    result->distances[start_vertex] = 0;
    queue[rear++] = start_vertex;
    result->visited_count = 1;
    
    while (front < rear) {
        int current = queue[front++];
        
        if (result->distances[current] > result->max_distance) {
            result->max_distance = result->distances[current];
            result->farthest_vertex = current;
        }
        
        for (int i = 0; i < graph->neighbor_count[current]; i++) {
            int neighbor = graph->adjacency_list[current][i];
            if (result->distances[neighbor] == -1) {
                result->distances[neighbor] = result->distances[current] + 1;
                queue[rear++] = neighbor;
                result->visited_count++;
            }
        }
    }
    
    free(queue);
    return result;
}

int find_graph_diameter(GraphStruct* graph) {
    if (graph == NULL || graph->vertex_count == 0) {
        return 0;
    }
    
    int global_diameter = -1;
    
    int* visited = (int*)calloc(graph->vertex_count, sizeof(int));
    
    for (int i = 0; i < graph->vertex_count; i++) {
        if (!visited[i]) {
            DistanceResult* comp_result = compute_distances_from_vertex(graph, i);
            
            if (comp_result->visited_count > 0) {
            
                for (int j = 0; j < graph->vertex_count; j++) {
                    if (comp_result->distances[j] != -1) {
                        visited[j] = 1;
                    }
                }
                
                int farthest = comp_result->farthest_vertex;
                free(comp_result->distances);
                free(comp_result);
                
                DistanceResult* diam_result = compute_distances_from_vertex(graph, farthest);
                int component_diameter = diam_result->max_distance;
                
                if (component_diameter > global_diameter) {
                    global_diameter = component_diameter;
                }
                
                free(diam_result->distances);
                free(diam_result);
            } else {
                free(comp_result->distances);
                free(comp_result);
            }
        }
    }
    
    free(visited);
    return global_diameter;
}
