// hash_table.c
#include "../include/hash_table.h"
#include "../include/struct.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// djb2 non-cryptographic hash
static uint64_t hash_function(const unsigned char* str) { // high bit set characters can become negative. 
    uint64_t hash = 5381; 

    while(*str) {
        hash = hash * 33 + *str++; // original way is bit manipulation.
    }

    return hash; 
}

// Return index
static uint64_t bucket_index(const uint64_t hash, int size) {
    return hash % size;
}

void print_node(struct node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", n->value);
    printf("------------------\n");
}

struct hash_table* create_table() { 
    const int default_size = 16;
    struct hash_table* kv_store = malloc(sizeof(*kv_store));
    if(kv_store == NULL) {
        printf("Memory allocation for kv_store in create_table failed");
        return NULL;
    }

    kv_store->cap = default_size;
    kv_store->buckets = calloc(kv_store->cap, sizeof(struct node*));

    if(kv_store->buckets == NULL) {
        free(kv_store);
        //free_hash_table(kv_store); // do i have to free all members if calloc fails?
        printf("Memory allocation for buckets in create_table failed");
        return NULL;
    }

    return kv_store;
}

// got a bug here
// make sure buckets zero initialized -> write test
// check should not be for null as well...
struct hash_table* insert(struct hash_table* kv_store, struct Arguments* arg1) { // returning hash_table for test purposes.
    // check for duplicate keys. 
    // testing
    // not calling from wrapper / will likely remove wrapper.
    if(get_value(kv_store, arg1->key)!=NULL) { // need to test after memory bug fixes.
        printf("The key provided is already in use.\n");
        return NULL;
    } 
    printf("INSERT key address=%p key=%s\n", (void*)arg1->key, arg1->key);
    uint64_t hash = bucket_index(hash_function((const unsigned char *)arg1->key), kv_store->cap);
    struct node* new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL) {
        printf("New node in insert failed allocation.");
        return NULL;
    }
    new_node->key = strdup(arg1->key);
    new_node->value = strdup(arg1->value); // write copy_value when i go to Value struct
    new_node->next = NULL;

    if(new_node->key==NULL || new_node->value==NULL) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return NULL;
    }

    if(kv_store->buckets[hash] == NULL) { // kv_store takes on ownership of nodes.
        kv_store->buckets[hash] = new_node;
        printf("Printing from expected new insertion point\n");
        print_node(kv_store->buckets[hash]);
    }
    else { // case of hash collision -> maybe this code should be moved
        struct node* tail = kv_store->buckets[hash];
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new_node;
        //print_node(tail);
        //print_node(tail->next); // need to write collision tests. actually have many tests to write
    }

    return kv_store; 
}

char* get_value(struct hash_table* kv_store, char* key) { // 
    
    //testing
    printf("GET key address=%p key=%s\n", (void*)key, key);

    if(kv_store == NULL || key == NULL) {
        //printf("No table has been created.\n"); // would definitely be caught sooner in execution
        return NULL;
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);
   
    struct node* curr = kv_store->buckets[hash];

    while(curr!=NULL) {
        if(strcmp(curr->key, key) == 0) {
            printf("%s\n",curr->value);
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
    
}

void free_hash_table(struct hash_table* kv_store) {
    if(kv_store == NULL) return;
    struct node* next;
    for(int i = 0; i < kv_store->cap; i++) {
        struct node* curr = kv_store->buckets[i];
        while(curr!=NULL) {
            free(curr->key);
            free(curr->value);
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(kv_store->buckets);
    free(kv_store);
    return;
}


/*int remove(struct hash_table* kv_store, char* key) {
    uint64_t hash = bucket_index(hash_function((const unsigned char *)arg1->key), kv_store->cap);
}*/