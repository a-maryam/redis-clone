// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "value.h"
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
    int size; // increment on insertion
};

struct hash_table* create_table();

void insert(struct hash_table** kv_store, char* key, struct Value* value);
void insert_no_resize(struct hash_table** kv_store, char* key, struct Value* value);
struct Value* get_value(struct hash_table* kv_store, char* key);

void delete_node(struct hash_table* kv_store, char* key);   
bool node_exists(struct hash_table* kv_store, char* key);
struct node* get_node(struct hash_table* kv_store, char* key);

void resize_table(struct hash_table** kv);
void copy_table(struct hash_table* old_kv, struct hash_table* new_kv);

void copy_node(struct node* old_n, struct node* new_n);
void print_node(struct node * n);

void free_hash_table(struct hash_table* kv_store);

#endif