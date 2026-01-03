// contain functions for different valuetyprs
#include "../include/struct.h"
#include "../include/value_functions.h"
#include <string.h>
#include "../include/hash_table.h"

// get command 
// create values
// insert into buckets

//Value* create_int_value(int x);
Value* create_string_value(const char* s) { // will be called based on command from user / cannot infer user-entered types
    Value* res = malloc(sizeof(*res));
    res->type = VALUE_STRING;
    res->data = s;
    res->size = strlen(s);
    res->destroy = destroy_string;
    res->copy = copy_string;
}

void destroy_string(Value* val) {
    free(val);
}

Value* copy_string(Value* old_value) {
    Value* new_value = malloc(sizeof(*new_value)); 
    new_value->type = old_value->type;
    new_value->data = old_value->data;
    new_value->size = old_value->size;
    new_value->destroy = old_value->destroy;
    new_value->copy = old_value->copy;
    return new_value;
}
