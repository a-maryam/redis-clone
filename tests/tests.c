// tests.c
// will contain all tests for now
#include <string.h>
#include <stdlib.h>
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"
#include "../include/commands.h"

/* hash table tests */
int test_kv_insert(struct Arguments* arg1) {
    struct hash_table* kv_store = create_table();
    set(kv_store, arg1);
    return 0;
}

int main(void) {
    struct Arguments* arg = malloc(sizeof(struct Arguments));
    arg->key = (char*)malloc(sizeof(9)); // "test_key\0"
    arg->value = (char*)malloc(sizeof(11)); // "test_value\0"

    strcpy(arg->key, "test_key");
    strcpy(arg->value, "test_value");

    test_kv_insert(arg); // simple test to see if key and value are inserted

    free_arg_struct(arg);

    return 0;
}

