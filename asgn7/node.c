// Author: Debi Majumdar
// Filename: node.c
// Assignment 7

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// Function to create a new Node with the given symbol and weight
Node *node_create(uint8_t symbol, uint32_t weight) {
    // Allocate memory for the new Node
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    // Initialize the Node fields
    new_node->symbol = symbol;
    new_node->weight = weight;
    new_node->code = 0;
    new_node->code_length = 0;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// Function to free memory occupied by the Node and its children
void node_free(Node **pnode) {
    if (*pnode != NULL) {
        // Recursively free memory for the left and right children
        node_free(&((*pnode)->left));
        node_free(&((*pnode)->right));

        // Free memory for the current Node
        free(*pnode);
        *pnode = NULL;
    }
}

// Helper function to print the Node and its children
void node_print_node(Node *tree, char ch, int indentation) {
    if (tree == NULL) {
        return;
    }

    // Print the right subtree
    node_print_node(tree->right, '/', indentation + 3);

    // Print the current Node's information
    printf("%*cweight = %d", indentation + 1, ch, tree->weight);

    // Print the symbol if it is a leaf Node
    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }

    printf("\n");

    // Print the left subtree
    node_print_node(tree->left, '\\', indentation + 3);
}

// Function to print the binary tree
void node_print_tree(Node *tree) {
    // Call the helper function to print the tree starting from the root
    node_print_node(tree, '<', 2);
}
