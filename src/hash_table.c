// hash_table.c
#include "../include/hash_table.h"
#include "../include/struct.h"
#include <stdint.h>
#include <stdlib.h>

// djb2 non-cryptographic hash
static uint64_t hash(const unsigned char* str) { // high bit set characters can become negative. 
    uint64_t hash = 5381; 

    while(*str) {
        hash = hash * 33 + *str++; // original way is bit manipulation.
    }

    return hash; 
}

static uint64_t bucket_index(const uint64_t hash, int size) {
    return hash % size;
}

struct hash_table* create_table(struct Arguments arg1) { // should createtable take the first value to add or simply allocate? 
    const int default_size = 16;
    struct hash_table* kv_store = malloc(sizeof(struct hash_table));
    kv_store->cap = default_size;
    kv_store->buckets = calloc(kv_store->cap, sizeof(struct node));
    return kv_store;
}
// when should the table be created? 

// who is going to create tables and who will free? 
// allocated here and caller should free I guess, function for freeing should be in this file


