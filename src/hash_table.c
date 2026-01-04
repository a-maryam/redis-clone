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

/*void print_node(struct node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", n->value->data);
    printf("------------------\n");
}*/

struct hash_table* create_table() { 
    const int default_size = 16;
    struct hash_table* kv_store = malloc(sizeof(*kv_store));

    if(kv_store == NULL) {
        printf("Memory allocation for kv_store in create_table failed");
        return NULL;
    }

    kv_store->cap = default_size;
    kv_store->buckets = calloc(kv_store->cap, sizeof(struct node*)); // pointers will be null (zero initialization)

    if(kv_store->buckets == NULL) {
        free(kv_store); // do not have to free buckets bc alloc failed
        printf("Memory allocation for buckets in create_table failed");
        return NULL;
    }

    return kv_store;
}

/* insert takes ownership for value in the case it fails to be inserted - otherwise it is freed when hashtable is */
void insert(struct hash_table* kv_store, char* key, struct Value* value) { 
    if(!kv_store || !key || !value) {
        value->destroy(value);
        return;
    }

    // check for duplicate keys. 
    struct node* n = get_node(kv_store, key);
    if (n) {
        n->value->destroy(n->value);
        n->value = value;
        return;
    }

    // testing
    //printf("INSERT key address=%p key=%s\n", (void*)arg1->key, arg1->key);
    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);
    struct node* new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL) {
        value->destroy(value); 
        printf("New node in insert failed allocation."); // logging ?
        return;
    }
    new_node->key = strdup(key);
    new_node->value = value; // do i need copy value?
    new_node->next = NULL;

    if(new_node->key==NULL) {
        free(new_node->key);
        new_node->value->destroy(new_node->value);
        free(new_node);
        return;
    }

    if(kv_store->buckets[hash] == NULL) { // kv_store takes on ownership of nodes.
        kv_store->buckets[hash] = new_node;
        //printf("Printing from expected new insertion point\n");
        //print_node(kv_store->buckets[hash]);
    }
    else { 
        struct node* tail = kv_store->buckets[hash];
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new_node;
        //print_node(tail);
        //print_node(tail->next); 
    }

    return; 
}

struct Value* get_value(struct hash_table* kv_store, char* key) { // 
    
    //testing
    //printf("GET key address=%p key=%s\n", (void*)key, key);

    if(kv_store == NULL || key == NULL) {
        return NULL;
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);
   
    struct node* curr = kv_store->buckets[hash];

    while(curr!=NULL) {
        if(strcmp(curr->key, key) == 0) {
            printf("%s\n",(char*)(curr->value->data)); // write print function
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
            curr->value->destroy(curr->value);
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(kv_store->buckets);
    free(kv_store);
    return;
}

void delete_node(struct hash_table* kv_store, char* key) { 
    if(kv_store == NULL || key == NULL) {
        return;
    }
    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);

    struct node* curr = kv_store->buckets[hash];
    struct node* prev = NULL;

    while(curr!=NULL) {
        if(strcmp(curr->key, key) == 0) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if(curr!=NULL) {
        if(prev!=NULL) { // middle of the list/end of list
            prev->next = curr->next;
            free(curr->key);
            curr->value->destroy(curr->value);
            free(curr);
            curr = NULL;
        }
        else { //head case
            kv_store->buckets[hash] = curr->next;
            free(curr->key);
            curr->value->destroy(curr->value);
            free(curr);
            curr=NULL;
        }
    } 
    else {
        printf("%s", "Entered key is not in key value store.\n");
    }

    return;
}

bool node_exists(struct hash_table* kv_store, char* key) {
    return false;
}

struct node* get_node(struct hash_table* kv_store, char* key) {
     if(kv_store == NULL || key == NULL) {
        return NULL;
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);
   
    struct node* curr = kv_store->buckets[hash];

    while(curr!=NULL) {
        if(strcmp(curr->key, key) == 0) {
            //printf("%s\n",(char*)(curr->value->data)); // write print function
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}