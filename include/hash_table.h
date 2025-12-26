// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "struct.h"

// hashtable stores strings until further notice
// hashtable = array of bucket heads, bucket is chain of node


// don't think typedefs are working for some reason. 
typedef struct node {
    char* key;
    struct Value value;
    struct node* next;
} node;

typedef struct hash_table {
    int cap; // capacity
    struct node** buckets;
} hash_table;

struct hash_table* create_table(struct Arguments arg1);

// buckets
// linkedlist
// chaining 

#endif