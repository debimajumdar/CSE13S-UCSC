#include "ll.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

LL * list_create()
{
	LL *l = (LL *)malloc(sizeof(LL));
	if (l == NULL) {
		return NULL;
	}
	l->head = NULL;
	return l;
}

bool list_add(LL *l, item *i)
{
	Node *n = (Node *)malloc(sizeof(Node));
	if (n == NULL) {
		return false;
	}
	n->data = *i;
	n->next = NULL;
	if (l->head == NULL) {
		l->head = n;
		return true;
	} else {
		Node *tail = l->head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = n;
		return true;
	}
}


item * list_find(LL *l, bool (*cmp)(item *,item *), item *i)
{
	Node *n = l->head;
        while (n != NULL) {
		if (cmp(&n->data, i)) {
			return &n->data;
		}
		n = n->next;
	}
	return NULL;
}
void list_destroy(LL **l) {
    if (*l == NULL) {
        return;
    }
    Node *current = (*l)->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(*l);
    *l = NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *current = l->head;
    Node *previous = NULL;
    while (current != NULL) {
        if (cmp(&current->data, i)) {
            if (previous == NULL) {
                l->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
