//author: Debi Majumdar
//filename: Path.c

#include "path.h"

#include "graph.h"
#include "stack.h"

#include <stdlib.h>

// Define the structure for the path
typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

// Function to create a new path
Path *path_create(uint32_t capacity) {
    // Allocate memory for the path structure
    Path *p = (Path *) malloc(sizeof(Path));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize path properties
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

// Function to free memory allocated for the path
void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        // Free memory for path vertices
        stack_free(&((*pp)->vertices));
        // Free memory for the path itself
        free(*pp);
        *pp = NULL;
    }
}

// Function to get the number of vertices in the path
uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

// Function to get the total distance of the path
uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

// Function to add a vertex to the path
void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t last_vertex;
    if (stack_peek(p->vertices, &last_vertex)) {
        p->total_weight += graph_get_weight(g, last_vertex, val);
    }
    stack_push(p->vertices, val);
}

// Function to remove a vertex from the path
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    if (stack_pop(p->vertices, &removed_vertex)) {
        uint32_t peeked;
        if (stack_peek(p->vertices, &peeked)) {
            p->total_weight -= graph_get_weight(g, peeked, removed_vertex);
        } else {
            p->total_weight = 0;
        }
    }
    return removed_vertex;
}

// Function to copy the contents of one path to another
void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

// Function to print the path
void path_print(const Path *p, FILE *f, const Graph *g) {
    stack_print(p->vertices, f, graph_get_names(g));
}
