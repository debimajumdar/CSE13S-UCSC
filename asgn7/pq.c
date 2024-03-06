// Author: Debi Majumdar
// Filename: pq.c
// Assignment 7

#include "pq.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Structure to represent elements in the priority queue
struct ListElement {
    Node *tree;
    struct ListElement *next;
};

// Structure to represent the priority queue
struct PriorityQueue {
    struct ListElement *list;
};

// Function to create a new priority queue
PriorityQueue *pq_create(void) {
    // Allocate memory for the new priority queue
    PriorityQueue *new_queue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (new_queue == NULL) {
        return NULL;
    }

    // Initialize the priority queue
    new_queue->list = NULL;

    return new_queue;
}

// Function to free memory occupied by the priority queue
void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

// Function to check if the priority queue is empty
bool pq_is_empty(PriorityQueue *q) {
    return (q == NULL || q->list == NULL);
}

// Function to check if the priority queue has a single element
bool pq_size_is_1(PriorityQueue *q) {
    return (q != NULL && q->list != NULL && q->list->next == NULL);
}

// Function to compare two list elements by weight and symbol
static bool pq_less_than(struct ListElement *e1, struct ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        return (e1->tree->symbol < e2->tree->symbol);
    }

    return false;
}

// Function to enqueue a tree into the priority queue
void enqueue(PriorityQueue *q, Node *tree) {
    // Allocate memory for the new list element
    struct ListElement *new_element = (struct ListElement *) malloc(sizeof(struct ListElement));
    if (new_element == NULL) {
        return;
    }

    // Initialize the new list element
    new_element->tree = tree;
    new_element->next = NULL;

    // Insert the new element into the priority queue
    if (pq_is_empty(q) || pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
    } else {
        struct ListElement *current = q->list;
        while (current->next != NULL && pq_less_than(current->next, new_element)) {
            current = current->next;
        }

        new_element->next = current->next;
        current->next = new_element;
    }
}

// Function to dequeue a tree from the priority queue
Node *dequeue(PriorityQueue *q) {
    // Check if the queue is empty
    if (pq_is_empty(q)) {
        fprintf(stderr, "Fatal error: Dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    // Remove and return the front element from the queue
    struct ListElement *front = q->list;
    q->list = front->next;
    Node *tree = front->tree;
    free(front);

    return tree;
}

// Function to print the priority queue
void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    struct ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }

        node_print_tree(e->tree);
        e = e->next;
        position++;
    }

    printf("=============================================\n");
}
