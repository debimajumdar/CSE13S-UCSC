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

