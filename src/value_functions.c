// contain functions for different valuetyprs
#include "../include/struct.h"
#include "../include/value_functions.h"
#include <string.h>
#include "../include/hash_table.h"
#include <stdlib.h>

//Value* create_int_value(int x) { TODO }

struct Value* create_string_value(char* s) { // will be called based on command from user / cannot infer user-entered types
    struct Value* res = malloc(sizeof(*res));
    if(!res) return NULL;
    res->type = VALUE_STRING;
    res->data = strdup(s); // get clear on ownership
    if(!res->data) return NULL;
    res->size = strlen(s);
    // function pointers
    res->destroy = destroy_string;
    res->copy = copy_string;
    return res;
}

void destroy_string(struct Value* val) {
    free(val->data); 
    free(val);
}

/* creates new value with all the data of old value */
struct Value* copy_string(struct Value* old_value) {
    struct Value* new_value = malloc(sizeof(*new_value)); 
    if(!new_value) return NULL;
    new_value->type = old_value->type;
    new_value->data = strdup(old_value->data);
    new_value->size = old_value->size;
    new_value->destroy = old_value->destroy;
    new_value->copy = old_value->copy;
    return new_value;
}
