//Author: Debi Majumdar
//Filename: uniqq.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h" // Include the hash table implementation

#define MAX_LINE_LENGTH 1024 // Maximum length of input line

int main() {
    // Create a hash table to store unique lines
    Hashtable *ht = hash_create();
    if (ht == NULL) {
        fprintf(stderr, "Error: Unable to create hash table\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    // Read lines from standard input until there are no more lines
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        // Remove trailing newline character, if present
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        // Check if the line is already in the hash table
        int *value = hash_get(ht, line);
        // If not, insert the line into the hash table
        if (value == NULL) {
            hash_put(ht, line, 1); // Value is not important, just using 1 as placeholder
        }
    }

    // Count the number of unique lines in the hash table
    int unique_count = 0;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        LL *bucket = ht->buckets[i];
        if (bucket != NULL) {
            Node *current = bucket->head;
            while (current != NULL) {
                unique_count++;
                current = current->next;
            }
        }
    }

    // Print the count of unique lines
    printf("%d\n", unique_count);

    // Destroy the hash table to free memory
    hash_destroy(&ht);

    return 0;
}
