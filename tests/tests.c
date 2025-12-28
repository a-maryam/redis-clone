// tests.c
// will contain all tests for now
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"
#include "../include/commands.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void print_node(struct node * n) {
    printf("------------------\n");
    printf("Printing a node\n");
    printf("Key: %s\n", n->key);
    printf("Node: %s\n", n->value);
    printf("------------------\n");
}

/* hash table tests */

/* tests insert and get - insert depends on a get or exists */ // logic??
bool test_kv_insert_and_get_value() {
    struct Arguments* arg = malloc(sizeof(struct Arguments));
    arg->key = (char*)malloc(sizeof(9)); // "test_key\0"
    arg->value = (char*)malloc(sizeof(11)); // "test_value\0"

    strcpy(arg->key, "test_key");
    strcpy(arg->value, "test_value");

    struct hash_table* kv = create_table();
    if(strcmp(get(kv, arg->key), arg->value)==0) {
        printf("%s compared to %s\n", get(kv, arg->key), arg->value);
        printf("kv_insert and get_value seem to be working."); // oop this logic should be in the test. will move
        // not sure if wrappers are neccessary in commands.h
    }
    free_arg_struct(arg);
}

// test empty get

// collision test 

// tests with more values

int main(void) {
    int total_tests = 1;
    int tests_passed = 0;
    //int tests_failed = 0;
    tests_passed+= (int) test_kv_insert_and_get_value();

    printf("%n/$n tests passed\n", tests_passed, total_tests);
    return 0;
}

