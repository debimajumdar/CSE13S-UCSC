//Author: Debi Majumdar
//Asgn6
//Filename: Surfin USA

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
Path *calculate_shortest_path(Graph *graph);
int calculate_next_permutation(uint32_t *array, uint32_t length);

int main(int argc, char *argv[]) {
    int directed = 0;
    char *input_file = NULL;
    char *output_file = NULL;

    // Go through command line options
    int opt;
    while ((opt = getopt(argc, argv, "dhi:o:")) != -1) {
        switch (opt) {
        case 'd': directed = 1; break;
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'h':
            printf("Usage: %s [options]\n", argv[0]);
            printf("Options:\n");
            printf("  -d                Specify the graph to be directed.\n");
            printf("  -i input_file     Specify the input file path containing the cities and "
                   "edges of a graph.\n");
            printf("  -o output_file    Specify the output file path to print to.\n");
            printf("  -h                Print out a help message describing the purpose of the "
                   "program and the command-line options it accepts, exiting the program "
                   "afterwards.\n");
            return 0;
        default:
            // Read from stdin as a default
            fprintf(stderr, "Invalid option\n");
            return 1;
        }
    }

    FILE *input;
    if (input_file == NULL) {
        input = stdin;
    } else {
        input = fopen(input_file, "r");
    }
    if (input == NULL) {
        fprintf(stderr, "Failed to open the input file.\n");
        return 1;
        return 1;
    }

    uint32_t num_vertices;
    fscanf(input, "%" SCNu32 "\n", &num_vertices);
    Graph *graph = graph_create(num_vertices, directed);

    char vertex_name[100];
    uint32_t i = 0;
    while (i < num_vertices) {
        // Read vertex names and add them to the graph
        fscanf(input, " %[^\n]\n", vertex_name);
        graph_add_vertex(graph, vertex_name, i);
        i++;
    }

    uint32_t num_edges;
    fscanf(input, "%" SCNu32, &num_edges);
    uint32_t j = 0;
    while (j < num_edges) {
        // Read edge information and add edges to the graph
        uint32_t start, end, weight;
        fscanf(input, "%" SCNu32 " %" SCNu32 " %" SCNu32, &start, &end, &weight);
        graph_add_edge(graph, start, end, weight);
        j++;
    }

    // Close the input file
    fclose(input);

    // Solve the TSP problem please
    Path *tsp_path = calculate_shortest_path(graph);

    // Print the TSP solution
    if (output_file != NULL) {
        FILE *output = fopen(output_file, "w");
        if (output != NULL) {
            if (path_distance(tsp_path) == 0) {
                fprintf(output, "No path found! Alissa is lost!\n");
            } else {
                fprintf(output, "Alissa starts at:\n");
                path_print(tsp_path, output, graph);
                fprintf(output, "Total Distance: %u\n", path_distance(tsp_path));
                fclose(output);
            }
        }
    } else {
        if (path_distance(tsp_path) == 0) {
            printf("No path found! Alissa is lost!\n");
        } else {
            printf("Alissa starts at:\n");
            path_print(tsp_path, stdout, graph);
            printf("Total Distance: %u\n", path_distance(tsp_path));
        }
    }

    // Free memory
    path_free(&tsp_path);
    graph_free(&graph);

    return 0;
}

void traverse_tsp(uint32_t current_vertex, Graph *graph, Path *current_path, Path *best_path) {
    graph_visit_vertex(graph, current_vertex);

    bool all_visited = true;
    uint32_t i = 0;
    while (i < graph_vertices(graph)) {
        if (!graph_visited(graph, i)) {
            all_visited = false;
            break;
        }
        i++;
    }

    if (all_visited) {
        if (graph_get_weight(graph, current_vertex, START_VERTEX)) {
            path_add(current_path, START_VERTEX, graph);
            if (path_distance(current_path) < path_distance(best_path)
                || 0 == path_distance(best_path)) {
                path_copy(best_path, current_path);
            }
            path_remove(current_path, graph);
        }

    } else {
        uint32_t j = 0;
        while (j < graph_vertices(graph)) {
            if (!graph_visited(graph, j) && graph_get_weight(graph, current_vertex, j) > 0) {
                path_add(current_path, j, graph);
                traverse_tsp(j, graph, current_path, best_path);
                path_remove(current_path, graph);
            }
            j++;
        }
    }

    graph_unvisit_vertex(graph, current_vertex);
}
Path *calculate_shortest_path(Graph *graph) {
    uint32_t num_vertices = graph_vertices(graph);
    Path *current_path = path_create(num_vertices + 1);
    Path *best_path = path_create(num_vertices + 1);

    // Start DFS from vertex 0
    path_add(current_path, 0, graph);
    traverse_tsp(0, graph, current_path, best_path);
    // Best path has a distance of 0
    path_free(&current_path);

    return best_path;
}
