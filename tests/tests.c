// tests.c
// will contain all tests for now
#include "../include/tests.h"
#include "../include/struct.h"
#include "../include/hash_table.h"
#include "../include/value_functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const int default_size = 16; // should this be a macro?

// rewrite tests to have size arg in create table call

// write string generator for short strings 
// loop to create a bunch of Values and insert into table
// test load factor

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

// main (driver) -> input -> args -> switchcase -> *create value if needed* -> call hashtable commands

/* hash table tests */

/* tests insert and get - insert is always going to depend on a get or exists */ 
bool test_kv_insert_and_get_value() {
    /* should make this const but I know my function does not modify.*/
    struct hash_table* kv = create_table(default_size);
    char* test_key = "TEST_KEY";
    char* test_val = "TEST_VALUE";
    struct Value* str_value = create_string_value(test_val);
    insert(&kv, test_key, str_value);

    // is the value in the hashtable what we want it to be for the key?
    int result = strcmp((char*)get_value(kv, test_key)->data, test_val); // strcmp equality is 0

    if(result==0) {
        printf("Insert and get test passed.\n");
    }
    else {
        printf("Insert and get test failed.\n");
    }

    free_hash_table(kv);

    return result == 0;
}

// create hash collisions
bool test_kv_insert_collision() {
    // "ab" "ba"
    struct hash_table* kv = create_table(default_size);

    char key1[] = "ab";
    char key2[] = "ba";
    char value1[] = "1";
    char value2[] = "2";

    struct Value* v1 = create_string_value(value1);
    struct Value* v2 = create_string_value(value2);

    insert(&kv, key1, v1);
    insert(&kv, key2, v2);

    char* res1 = (char*) get_value(kv, key1)->data;
    char* res2 = (char*) get_value(kv, key2)->data;
    
    // checking if both args have been inserted and that they exist in different memory.
    bool result = res1!=NULL && res2!=NULL && res1!=res2;

    if(result) {
        printf("collision test passed.\n");
    }
    else {
        printf("collision test failed.\n");
    }

    free_hash_table(kv);

    return result;
}

/* Testing get independently of insert */
bool test_kv_get_value_when_empty() {
    struct hash_table* kv = create_table(default_size);
    char key[] = "DNE";
    bool res = get_value(kv, key) == NULL;
    free_hash_table(kv);
    if(!res) printf("Get value on empty table is not null. Test failed.\n");
    return res;
}

bool test_delete() {
    struct hash_table* kv = create_table(default_size);

    char key[] = "ABC";
    char value[] = "123";
    struct Value* v1 = create_string_value(value);

    insert(&kv, key, v1);
    delete_node(kv, key);

    bool res = get_value(kv, key) == NULL;

    free_hash_table(kv);

    return res;
}

// test that calloc is initing kvstore 

// tests with more values, tempt more collisions

// implement exists (maybe too similar to get -- guess its just a boring bool func)

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

