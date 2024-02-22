//Author: Debi Majumdar
//Filename: hash.c

#include "hash.h"

#include <stdlib.h>
#include <string.h>

// Hash function to calculate the index of the bucket
unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % NUM_BUCKETS;
}

Hashtable *hash_create(void) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    if (ht == NULL) {
        return NULL;
    }
    for (int i = 0; i < NUM_BUCKETS; i++) {
        ht->buckets[i] = list_create();
        if (ht->buckets[i] == NULL) {
            // Cleanup if memory allocation fails
            for (int j = 0; j < i; j++) {
                list_destroy(&ht->buckets[j]);
            }
            free(ht);
            return NULL;
        }
    }
    return ht;
}

bool hash_put(Hashtable *ht, char *key, int val) {
    unsigned int index = hash_function(key);
    if (ht->buckets[index] == NULL) {
        return false; // Bucket does not exist
    }
    item item_to_insert;
    strncpy(item_to_insert.key, key, sizeof(item_to_insert.key));
    item_to_insert.id = val;
    return list_add(ht->buckets[index], &item_to_insert);
}

int *hash_get(Hashtable *ht, char *key) {
    unsigned int index = hash_function(key);
    if (ht->buckets[index] == NULL) {
        return NULL; // Bucket does not exist
    }
    item key_to_find;
    strncpy(key_to_find.key, key, sizeof(key_to_find.key));
    item *found_item = list_find(ht->buckets[index], cmp, &key_to_find);
    if (found_item == NULL) {
        return NULL; // Key not found
    }
    return &(found_item->id);
}

void hash_destroy(Hashtable **ht) {
    if (*ht == NULL) {
        return;
    }
    for (int i = 0; i < NUM_BUCKETS; i++) {
        list_destroy(&((*ht)->buckets[i]));
    }
    free(*ht);
    *ht = NULL;
}
