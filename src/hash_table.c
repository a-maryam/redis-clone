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

void resize_table(struct hash_table** kv) {
    struct hash_table* old_kv = *kv;
    struct hash_table* new_kv = create_table(old_kv->cap * 2);
    if(!new_kv) return;
    copy_table(old_kv, new_kv);
    free_hash_table(old_kv); 
    *kv = new_kv;
    return;
}

void copy_table(struct hash_table* old_kv, struct hash_table* new_kv) {
    for(int i = 0; i < old_kv->cap; i++) {
        struct node* old_curr = old_kv->buckets[i];

        while(old_curr!=NULL) {
            struct Value* new_val = old_curr->value->copy(old_curr->value);
            insert_no_resize(&new_kv, old_curr->key, new_val); // insert owns key: key strdup there
            old_curr = old_curr->next;
        }
    }
    return;
}

void copy_node(struct node* old_n, struct node* new_n) {
    new_n->key = strdup(old_n->key);
    new_n->value = old_n->value->copy(old_n->value);
    new_n->next = NULL;
}

void print_node(struct node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", (char*)n->value->data);
    printf("------------------\n");
}

struct hash_table* create_table(int capacity) { 
    struct hash_table* kv_store = malloc(sizeof(*kv_store));

    if(kv_store == NULL) {
        printf("Memory allocation for kv_store in create_table failed");
        return NULL;
    }

    kv_store->cap = capacity;
    kv_store->buckets = calloc(kv_store->cap, sizeof(struct node*)); // pointers will be null (zero initialization)
    kv_store->size = 0;

    if(kv_store->buckets == NULL) {
        free(kv_store); // do not have to free buckets bc alloc failed
        printf("Memory allocation for buckets in create_table failed");
        return NULL;
    }

    return kv_store;
}

// i feel like this may be bad design but since we keep looping after command failures it seems necessary
/* insert takes ownership for value - then when in table owned by table */
void insert(struct hash_table** kv_store, char* key, struct Value* value) { 
    bool test = true;
    if(!kv_store || !key || !value) {
        value->destroy(value);
        return;
    }

    // check for duplicate keys. 
    struct node* n = get_node(*kv_store, key);
    if (n) {
        n->value->destroy(n->value);
        n->value = value;
        printf("%s\n", "duplicate");
        // overwrite should not increment
        //(*kv_store)->size = (*kv_store)->size + 1;
        return;
    }
    double load_factor = 0.75;
    //load_factor = 0.0; // test

    // check load factor
    if((double)(*kv_store)->size / (*kv_store)->cap >= load_factor) {
        resize_table(kv_store);
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), (*kv_store)->cap);
    struct node* new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL) {
        value->destroy(value); 
        if(test) printf("New node in insert failed allocation."); // logging ?
        if(test) printf("%s\n", "early return in insert. new node allocated null");
        return;
    }
    new_node->key = strdup(key);
    
    if(new_node->key==NULL) {
        value->destroy(value);
        free(new_node);
        return;
    }

    new_node->value = value; // do i need copy value?
    new_node->next = NULL;

    if((*kv_store)->buckets[hash] == NULL) { // kv_store takes on ownership of nodes.
        (*kv_store)->buckets[hash] = new_node;
    }
    else { 
        struct node* tail = (*kv_store)->buckets[hash];
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new_node;
    }
   
    (*kv_store)->size = (*kv_store)->size + 1;
    return; 
}

// can probably rewrite this to take hash_table* or can add a param to regular insert and remove this
void insert_no_resize(struct hash_table** kv_store, char* key, struct Value* value) { 
    if(!kv_store || !key || !value) {
        value->destroy(value);
        return;
    }

    // check for duplicate keys. 
    struct node* n = get_node(*kv_store, key);
    if (n!=NULL) {
        n->value->destroy(n->value);
        n->value = value;
        return;
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), (*kv_store)->cap);
    struct node* new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL) {
        value->destroy(value); 
        printf("New node in insert failed allocation."); // logging ?
        return;
    }
    new_node->key = strdup(key);
    
    if(new_node->key==NULL) {
        value->destroy(value);
        free(new_node);
        return;
    }

    new_node->value = value; // do i need copy value?
    new_node->next = NULL;

    if((*kv_store)->buckets[hash] == NULL) { // kv_store takes on ownership of nodes.
        (*kv_store)->buckets[hash] = new_node;
    }
    else { 
        struct node* tail = (*kv_store)->buckets[hash];
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new_node;
    }

    (*kv_store)->size = (*kv_store)->size + 1;
    return; 
}

struct Value* get_value(struct hash_table* kv_store, char* key) { // 
    if(kv_store == NULL || key == NULL) {
        return NULL;
    }

    uint64_t hash = bucket_index(hash_function((const unsigned char *)key), kv_store->cap);
   
    struct node* curr = kv_store->buckets[hash];

    // memory used here must have been freed.
    while(curr!=NULL) {
        if(strcmp(curr->key, key) == 0) {
            //printf("printing string value:%s\n",(char*)(curr->value->data)); // write print function
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
    // decrement size
    // make sure size stays the same if not found
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
        else { // head case
            kv_store->buckets[hash] = curr->next;
            free(curr->key); // going to have to malloc even in tests.
            curr->value->destroy(curr->value);
            free(curr);
            curr=NULL;
        }
        kv_store->size-=1;
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
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}