#ifndef _HASH

#define _HASH

#include "ll.h"
#define NUM_BUCKETS 1000 // Number of buckets in the hash table
typedef struct Hashtable Hashtable;

struct Hashtable {
    LL *buckets[NUM_BUCKETS];
    // Array of linked lists for storing key-value pairs
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
