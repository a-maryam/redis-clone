// tests.c
// will contain all tests for now
#include <string.h>
#include <stdlib.h>
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"
#include "../include/commands.h"

static void print_node(struct node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", n->value);
    printf("------------------\n");
}

/* hash table tests */
struct hash_table* test_kv_insert(struct Arguments* arg1) {
    struct hash_table* kv_store = create_table();
    set(kv_store, arg1);
    return kv_store; // should be the mutated one
}

int main(void) {
    struct Arguments* arg = malloc(sizeof(struct Arguments));
    arg->key = (char*)malloc(sizeof(9)); // "test_key\0"
    arg->value = (char*)malloc(sizeof(11)); // "test_value\0"

    strcpy(arg->key, "test_key");
    strcpy(arg->value, "test_value");

    struct hash_table* kv = test_kv_insert(arg); // simple test to see if key and value are inserted
    // strcmp(get(kv, arg), kv->value)
    free_arg_struct(arg);

    return 0;
}

