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


// create new argument structs more easily.
// caller will own memory allocated here. must free.
static struct Arguments* create_new_arguments(char* key1, char* value1, enum Command cmd1) { // string 
    struct Arguments* arg = malloc(sizeof(struct Arguments));

    arg->key = malloc(strlen(key1)+1); // "test_key\0"
    arg->value = malloc(strlen(value1)+1); // "test_value\0"
    arg->command = cmd1;

    strcpy(arg->key, key1);
    strcpy(arg->value, value1);

    return arg;
}

/* hash table tests */

/* tests insert and get - insert depends on a get or exists */ // logic??
bool test_kv_insert_and_get_value() {
    struct Arguments* arg = malloc(sizeof(struct Arguments));
    arg->key = malloc(9); // "test_key\0"
    arg->value = malloc(11); // "test_value\0"
    arg->command = CMD_SET; // actually unnecessary here

    strcpy(arg->key, "test_key");
    strcpy(arg->value, "test_value");

    struct hash_table* kv = create_table();

    insert(kv, arg);

    int result = strcmp(get(kv, arg->key), arg->value); // strcmp equality is 0

    if(result==0) {
        printf("Insert and get test passed.\n");
    }
    else {
        printf("Insert and get test failed.\n");
    }

    free_arg_struct(arg);
    free_hash_table(kv);

    return result == 0;
}

bool test_kv_insert_collision() {
    // cause same hash
    // "ab" "ba"
    struct hash_table* kv = create_table();

    char key1[] = "ab";
    char key2[] = "ba";
    char value1[] = "1";
    char value2[] = "2";

    struct Arguments* arg1 = create_new_arguments(key1, value1, CMD_SET);
    struct Arguments* arg2 = create_new_arguments(key2, value2, CMD_SET);

    insert(kv, arg1);
    insert(kv, arg2);
    
    bool result = (get(kv, arg1->key)!=NULL) && (get(kv, arg2->key)!=NULL);

    if(result) {
        printf("collision test passed.\n");
    }
    else {
        printf("collision test failed.");
    }

    free_arg_struct(arg1);
    free_arg_struct(arg2);
    free_hash_table(kv);

    return result;
}

/* Testing get independently of insert */
/*bool test_kv_get_value_when_empty() {

}*/

// tests with more values, tempt more collisions

// implement exists (maybe too similar to get -- guess its just a boring bool func)
// implement delete
// onto TCP server after

int main(void) {
    int total_tests = 2;
    int tests_passed = 0;
    //int tests_failed = 0;
    tests_passed+= (int) test_kv_insert_and_get_value();
    tests_passed+= (int) test_kv_insert_collision();

    printf("%d out of %d tests passed\n", tests_passed, total_tests);
    return 0;
}

