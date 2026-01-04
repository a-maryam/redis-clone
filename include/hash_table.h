// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "struct.h"
#include <stdbool.h>

// represents key value pair
struct node {
    char* key;
    struct Value* value; // rewriting for abstraction
    struct node* next;
};

struct hash_table {
    int cap; // capacity
    struct node** buckets; // linkedlist of linkedlist
};

struct hash_table* create_table();
void insert(struct hash_table* kv_store, char* key, struct Value* value);
struct Value* get_value(struct hash_table* kv_store, char* key);
void delete_node(struct hash_table* kv_store, char* key);  // probably make it return void. 
bool node_exists(struct hash_table* kv_store, char* key);

void free_hash_table(struct hash_table* kv_store);
void print_node(struct node * n);
#endif