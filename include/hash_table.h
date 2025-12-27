// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "struct.h"
#include <stdbool.h>

// don't think typedefs are working for some reason. 
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
struct hash_table* get_value(struct hash_table*, char* key);
struct hash_table* delete_key(struct hash_table*, char* key);
bool key_exists(struct hash_table*, char* key);

void free_hash_table(struct hash_table* kv_store);

#endif