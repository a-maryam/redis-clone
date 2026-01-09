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
#include <time.h>

const int default_size = 16; // should this be a macro or in header file?
const double load_factor = 0.75;

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

// create hash collisions in unresized table 
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

bool resize_and_collision_test() {
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

    resize_table(&kv);

    char* new_res1 = (char*) get_value(kv, key1)->data;
    char* new_res2 = (char*) get_value(kv, key2)->data;
    bool result2 = new_res1!=NULL && new_res2!=NULL && new_res1!=new_res2;

    free_hash_table(kv);

    return result && result2;
}

bool reinsert_deleted_key() {
    struct hash_table* kv = create_table(default_size);

    char key[] = "key";
    char value[]="value";
    struct Value* new_val = create_string_value(value);

    insert(&kv, key, new_val);

    bool res0 = kv->size == 1;

    delete_node(kv, key); 
    bool res1 = kv->size == 0;

    struct Value* new_val2 = create_string_value(value);

    insert(&kv, key, new_val2);

    bool res2 = (strcmp((char*)get_value(kv, key)->data, value) == 0);
    bool res3 = kv->size == 1;

    free_hash_table(kv);

    return res0 && res1 && res2 && res3;
}

// caller must free
char* generate_random_string(int len) {
    // want random numbers from 32-122 (includes some symbols)
    char* random_string = malloc((len+1)*sizeof(char));
    if(random_string == NULL) return NULL;
    char buffer[len+1];
    buffer[len] = '\0';
    int lower = 32;
    int upper = 122;
    for(int i = 0; i < len; i++) {
        buffer[i] = (char) ((rand() % (upper - lower +1)) + lower);
    }
    strcpy(random_string, buffer);
    return random_string;
}


bool insert_many_delete_all_destroy_table() {
    struct hash_table* kv = create_table(default_size);
    int len_keys = 14;
    int len_values = 14;
    int num_to_insert = 1000;

    // +1 for termination
    char** keys = malloc(num_to_insert*sizeof(char*));
    struct Value** vals = calloc(num_to_insert, sizeof(struct Value*));
    for(int i = 0; i < num_to_insert; i++) {
        char* temp = generate_random_string(len_values+1);
        //printf("key: %s\n", temp);
        vals[i] = create_string_value(temp);
        keys[i] = generate_random_string(len_keys+1);
        free(temp); // create value mallocs/strdups its own string
    }

    for(int i = 0; i < num_to_insert; i++) {
        insert(&kv, keys[i], vals[i]);
    }
    bool res0 = kv->size == num_to_insert;

    for(int i = 0; i < num_to_insert; i++) {
        delete_node(kv, keys[i]);
    }
    bool res1 = kv->size == 0;

    // destroy
    for(int i = 0 ; i < num_to_insert; i++) {
        free(keys[i]);
    }
    free(keys);
    free(vals);
    free_hash_table(kv);

    return res0 && res1;
}

bool insert_same_key() {
    struct hash_table* kv = create_table(default_size);
    int len = 10;
    char* key = generate_random_string(len);
    char* value = generate_random_string(len); // doesn't particularly matter but we'll insert same value too

    struct Value* new_val = create_string_value(value);
    insert(&kv, key, new_val);
    bool res0 = kv->size == 1;
    struct Value* new_val1 = create_string_value(value);
    insert(&kv, key, new_val1);
    bool res1 = kv->size == 1;
    
    free_hash_table(kv);
    free(key);
    free(value);
    return res0 && res1;
}


/* Insert keys to trigger resize, delete keys, trigger new resize by insert. */
bool insert_many_delete_all_reinsert_destroy_table() {
    struct hash_table* kv = create_table(default_size);
    int len_keys = 14;
    int len_values = 14;
    int num_to_insert = 3 * default_size / 4; // 

    // +1 for termination
    char** keys = malloc(num_to_insert*sizeof(char*));
    struct Value** vals = calloc(num_to_insert, sizeof(struct Value*));
    for(int i = 0; i < num_to_insert; i++) {
        char* temp = generate_random_string(len_values+1);
        vals[i] = create_string_value(temp);
        keys[i] = generate_random_string(len_keys+1);
        free(temp); // create value mallocs/strdups its own string
    }

    for(int i = 0; i < num_to_insert; i++) {
        insert(&kv, keys[i], vals[i]);
    }
    bool res0 = kv->size == num_to_insert;
    bool res1 = kv->cap == default_size * 2;

    for(int i = 0; i < num_to_insert; i++) {
        delete_node(kv, keys[i]);
    }
    bool res2 = kv->size == 0;

    // destroy
    for(int i = 0 ; i < num_to_insert; i++) {
        free(keys[i]);
    }


    free(keys);
    free(vals);
    free_hash_table(kv);

    return res0 && res1;
}

// test that calloc is initing kvstore 
// implement exists (maybe too similar to get -- guess its just a boring bool func)

int main(void) {
    // should be called once in main -- otherwise nonrandomness happens
    srand(time(NULL));

    int total_tests = 8;
    int tests_passed = 0;
    
    tests_passed+= (int) test_kv_insert_and_get_value();
    tests_passed+= (int) test_kv_insert_collision();
    tests_passed+= (int) test_kv_get_value_when_empty();
    tests_passed+= (int) test_delete();
    tests_passed+= (int) resize_and_collision_test();
    tests_passed+= (int) reinsert_deleted_key();
    tests_passed+= (int) insert_many_delete_all_destroy_table();
    tests_passed+= (int) insert_same_key();

    //printf("generated string: %s\n", generate_random_string(13));

    printf("%d out of %d tests passed\n", tests_passed, total_tests);
    printf("%d tests failed\n", total_tests - tests_passed);
    return 0;
}

// Resize, delete keys, resize again
// Edge case tests
// Invariant tests
