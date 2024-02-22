//Author: Debi Majumdar
//Filename: ll.c

#include "ll.h"

#include <stdbool.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL; //We are going to Initialize tail pointer to NULL
    return l;
}

bool list_add(LL *l, item *i) {
    if (l == NULL || i == NULL) {
        return false;
    }

    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;

    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n; // We will Update the tail pointer
    return true;
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    if (l == NULL || cmp == NULL || i == NULL) {
        return NULL;
    }

    Node *current = l->head;
    while (current != NULL) {
        if (cmp(&current->data, i)) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
}

void list_destroy(LL **l) {
    if (l == NULL || *l == NULL) {
        return;
    }

    Node *current = (*l)->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(*l);
    *l = NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    if (l == NULL || cmp == NULL || i == NULL) {
        return;
    }

    Node *current = l->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (cmp(&current->data, i)) {
            if (prev == NULL) {
                l->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == l->tail) {
                l->tail = prev;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
