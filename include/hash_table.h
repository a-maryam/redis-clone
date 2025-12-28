// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "struct.h"
#include <stdbool.h>

// represents key value pair
struct node {
    char* key;
    char* value; // change to Value struct
    struct node* next;
};

struct hash_table {
    int cap; // capacity
    struct node** buckets; // linkedlist of linkedlist
};

struct hash_table* create_table();
struct hash_table* insert(struct hash_table* kv_store, struct Arguments* arg1);
char* get_value(struct hash_table* kv_store, char* key);
struct hash_table* delete_key(struct hash_table* kv_store, char* key);
bool key_exists(struct hash_table* kv_store, char* key);

void free_hash_table(struct hash_table* kv_store);

#endif