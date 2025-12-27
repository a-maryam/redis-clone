// hash_table.c
#include "../include/hash_table.h"
#include "../include/struct.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// djb2 non-cryptographic hash
static uint64_t hash_function(const unsigned char* str) { // high bit set characters can become negative. 
    uint64_t hash = 5381; 

    while(*str) {
        hash = hash * 33 + *str++; // original way is bit manipulation.
    }

    return hash; 
}

static uint64_t bucket_index(const uint64_t hash, int size) {
    return hash % size;
}

/* Functions for testing purposes */
static void print_node(node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", n->value);
    printf("------------------\n");
}

struct hash_table* create_table() { // should createtable take the first value to add or simply allocate? 
    const int default_size = 16;
    struct hash_table* kv_store = malloc(sizeof(struct hash_table));
    if(kv_store == NULL) {
        printf("Memory allocation for kv_store in create_table failed");
        return NULL;
    }

    kv_store->cap = default_size;
    kv_store->buckets = calloc(kv_store->cap, sizeof(struct node));

    if(kv_store->buckets == NULL) {
        printf("Memory allocation for buckets in create_table failed");
        return NULL;
    }

    return kv_store;
}

int insert(struct hash_table* kv_store, struct Arguments* arg1) {
    uint64_t hash = bucket_index(hash_function((const unsigned char *)arg1->key), kv_store->cap);
    struct node* new_node = malloc(sizeof(struct node));
    if(new_node == NULL) {
        printf("New node in insert failed allocation.");
    }
    new_node->key = strdup(arg1->key);
    new_node->value = strdup(arg1->value); // write copy_value when i go to Value struct
    new_node->next = NULL;

    if(kv_store->buckets[hash] == NULL) {
        kv_store->buckets[hash] = new_node;
        printf("Printing from expected new insertion point\n");
        print_node(kv_store->buckets[hash]);
    }
    else { // case of hash collision -> maybe this code should be moved
        struct node* temp = kv_store->buckets[hash];
        struct node* tail;
        while(temp!=NULL) {
            tail = temp;
            temp = temp->next;
        }
        tail->next = new_node;
        print_node(tail);
        print_node(tail->next); // need to write collision tests. actually have many tests to write
    }

    return 0; 
}

/*int remove(struct hash_table* kv_store, char* key) {
    uint64_t hash = bucket_index(hash_function((const unsigned char *)arg1->key), kv_store->cap);
}*/


// when should the table be created? created in main(), needs to be held onto.

// who is going to create tables and who will free? 
// allocated here and caller should free I guess, function for freeing should be in this file


