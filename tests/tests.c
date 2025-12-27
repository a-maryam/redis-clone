// tests.c
// will contain all tests for now
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"

/* hash table tests */
int test_kv_insert(struct Arguments* arg1) {
    struct hash_table* kv_store = create_table();
    set(kv_store, arg1);
    return 0;
}

