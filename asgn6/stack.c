//Author: Debi Majumdar
//filename: Stack.c

#include "stack.h"

#include <assert.h>
#include <stdlib.h>

// Define the structure for the stack
typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

// Function to create a new stack
Stack *stack_create(uint32_t capacity) {
    // Allocate memory for the stack structure
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize stack properties
    s->capacity = capacity;
    s->top = 0;

    // Allocate memory for stack items
    s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
    if (s->items == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return s;
}

// Function to free memory allocated for the stack
void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        // Free memory for stack items
        if ((*sp)->items != NULL) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        // Free memory for the stack itself
        free(*sp);
    }
    if (sp != NULL) {
        *sp = NULL;
    }
}

// Function to push an element onto the stack
bool stack_push(Stack *s, uint32_t val) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = val;
    s->top++;
    return true;
}

// Function to pop an element from the stack
bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *val = s->items[s->top];
    return true;
}

// Function to peek at the top element of the stack
bool stack_peek(const Stack *s, uint32_t *val) {
    if (stack_empty(s)) {
        return false;
    }
    *val = s->items[s->top - 1];
    return true;
}

// Function to check if the stack is empty
bool stack_empty(const Stack *s) {
    return s->top == 0;
}

// Function to check if the stack is full
bool stack_full(const Stack *s) {
    return s->top == s->capacity;
}

// Function to get the size of the stack
uint32_t stack_size(const Stack *s) {
    return s->top;
}

// Function to copy the contents of one stack to another
void stack_copy(Stack *dst, const Stack *src) {
    assert(dst->capacity >= src->top);
    dst->top = src->top;
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }
}

// Function to print the contents of the stack
void stack_print(const Stack *s, FILE *f, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(f, "%s\n", cities[s->items[i]]);
    }
}
