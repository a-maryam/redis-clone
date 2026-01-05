// tests.c
// will contain all tests for now
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// create new argument structs more easily.
// caller will own memory allocated here. must free.
static struct Arguments* create_new_arguments(char* key1, char* value1, enum Command cmd1) { // string 
    struct Arguments* arg = malloc(sizeof(*arg));

    arg->key = malloc(strlen(key1)+1); // "test_key\0"
    arg->value = malloc(strlen(value1)+1); // "test_value\0"
    arg->command = cmd1;

    strcpy(arg->key, key1);
    strcpy(arg->value, value1);

    return arg;
}

/* hash table tests */

/* tests insert and get - insert is always going to depend on a get or exists */ 
bool test_kv_insert_and_get_value() {
    // create arg to insert into table
    struct Arguments* arg = malloc(sizeof(*arg));
    arg->key = malloc(strlen("test_key")+1); // "test_key\0"
    arg->value = malloc(Sstrlen("test_value")+1); // "test_value\0"
    arg->command = SSET; // actually unnecessary here

    // copy test values into arg
    strcpy(arg->key, "test_key");
    strcpy(arg->value, "test_value");

    struct hash_table* kv = create_table();

    insert(kv, arg);

    // is the value in the hashtable what we want it to be for the key?
    int result = strcmp(get_value(kv, arg->key), arg->value); // strcmp equality is 0

    if(result==0) {
        printf("Insert and get test passed.\n");
    }
    else {
        printf("Insert and get test failed.\n");
    }

    // freeing memory we own
    free_arg_struct(arg);
    free_hash_table(kv);

    return result == 0;
}

// create hash collisions
bool test_kv_insert_collision() {
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

    char* res1 = get_value(kv, arg1->key);
    char* res2 = get_value(kv, arg2->key);
    
    // checking if both args have been inserted and that they exist in different memory.
    bool result = res1!=NULL && res2!=NULL && res1!=res2;

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
bool test_kv_get_value_when_empty() {
    struct hash_table* kv = create_table();
    char key[] = "DNE";
    bool res = get_value(kv, key) == NULL;
    free_hash_table(kv);
    if(!res) printf("Get value on empty table is not null. Test failed.");
    return res;
}

bool test_delete() {
    struct hash_table* kv = create_table();
    char key[] = "ABC";
    char value[] = "123";
    struct Arguments* arg1 = create_new_arguments(key, value, CMD_SET);
    insert(kv, arg1);
    delete_node(kv, key);
    free_arg_struct(arg1);
    free_hash_table(kv);
    return get_value(kv, key) == NULL;
}

// test that calloc is initing kvstore 

// tests with more values, tempt more collisions

// implement exists (maybe too similar to get -- guess its just a boring bool func)
// implement delete

int main(void) {
    int total_tests = 4;
    int tests_passed = 0;
    
    tests_passed+= (int) test_kv_insert_and_get_value();
    tests_passed+= (int) test_kv_insert_collision();
    tests_passed+= (int) test_kv_get_value_when_empty();
    tests_passed+= (int) test_delete();

    printf("%d out of %d tests passed\n", tests_passed, total_tests);
    printf("%d tests failed\n", total_tests-tests_passed);
    return 0;
}

