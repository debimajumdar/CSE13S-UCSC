#ifndef _HASH

#define _HASH 

#include "ll.h"

typedef struct Hashtable Hashtable;

struct Hashtable {
	// your datastructure here; this is just a placeholder
	int h;
};

Hashtable * hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int * hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
