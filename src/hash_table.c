// hash_table.c
#include "../include/hash_table.h"
#include "../include/struct.h"
#include <stdint.h>

// djb2 non-cryptographic hash
static uint64_t hash(const unsigned char* str) { // high bit set characters can become negative. 
    uint64_t hash = 5381; 

    while(*str) {
        hash = hash * 33 + *str++; // original way is bit manipulation.
    }

    return hash; 
}

static int index(const uint64_t hash, int size) {
    return hash % size;
}

int create_table(struct Arguments arg1) { // should createtable take the first value to add or simply allocate? 
    const int default_size = 16;
    struct hash_table* kv_store = malloc(sizeof(*hash_table));
    kv_store -> size = default_size;
    kv_store -> buckets = malloc(sizeof(struct *node));
    struct node* 
    for(int i = 0; i < default_size; i++) {
        kv_store = malloc(line_length * sizeof(*line));

    if(line == NULL) {
        printf("Memory allocation for line failed\n");
        return NULL;
    }
    }
}
// when should the table be created? 

// who is going to create tables and who will free? 
// allocated here and caller should free I guess, function for freeing should be in this file


