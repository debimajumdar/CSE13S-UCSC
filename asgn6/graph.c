#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the graph
struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
};

// Function to create a new graph
Graph *graph_create(uint32_t vertices, bool directed) {
    // Allocate memory for the graph structure
    Graph *g = (Graph *) calloc(1, sizeof(Graph));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize graph properties
    g->vertices = vertices;
    g->directed = directed;

    // Allocate memory for the visited array
    g->visited = (bool *) calloc(vertices, sizeof(bool));
    if (g->visited == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for vertex names
    g->names = (char **) calloc(vertices, sizeof(char *));
    if (g->names == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for edge weights
    g->weights = (uint32_t **) calloc(vertices, sizeof(uint32_t *));
    if (g->weights == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row in the weights matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = (uint32_t *) calloc(vertices, sizeof(uint32_t));
        if (g->weights[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

// Function to free memory allocated for the graph
void graph_free(Graph **gp) {
    // Check if the graph pointer and graph exist
    if (gp != NULL && *gp != NULL) {
        // Free memory for names and weights arrays
        for (uint32_t i = 0; i < (*gp)->vertices; ++i) {
            free((*gp)->names[i]);
            free((*gp)->weights[i]);
        }
        free((*gp)->names);
        free((*gp)->weights);
        
        // Free memory for the visited array and the graph itself
        free((*gp)->visited);
        free(*gp);
    }
    
    // Set the graph pointer to NULL after freeing memory
    if (gp != NULL) {
        *gp = NULL;
    }
}

// Function to get the number of vertices in the graph
uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

// Function to add a vertex to the graph
void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    // Free memory if the vertex name already exists
    if (g->names[v]) {
        free(g->names[v]);
    }
    
    // Allocate memory for the new vertex name and copy it
    g->names[v] = strdup(name);
}

// Function to get the name of a vertex in the graph
const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

// Function to get all vertex names in the graph
char **graph_get_names(const Graph *g) {
    return g->names;
}

// Function to add an edge between two vertices in the graph
void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    // Set the weight of the edge between start and end vertices
    g->weights[start][end] = weight;
    
    // If the graph is undirected, set the weight of the reverse edge
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
}

// Function to get the weight of an edge between two vertices in the graph
uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

// Function to mark a vertex as visited in the graph
void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

// Function to mark a vertex as unvisited in the graph
void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}

// Function to check if a vertex is visited in the graph
bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

// Function to print information about the graph
void graph_print(const Graph *g) {
    printf("Number of Vertices: %u\n", g->vertices);

    printf("Names of Vertices:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%s\n", g->names[i]);
    }

    uint32_t num_edges = 0;

    printf("Edges:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            uint32_t weight = g->weights[i][j];
            if (weight > 0) {
                printf("%u %u %u\n", i, j, weight);
                num_edges++;
            }
        }
    }
    printf("Number of Edges: %u\n", num_edges);
}
