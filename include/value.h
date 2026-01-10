/* value.h 
Purpose: so far hold structs used at the heart of the key-value store
*/

#ifndef VALUE_H
#define VALUE_H
#include <stddef.h>

enum ValueType {
    VALUE_FLOAT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_INT,
    VALUE_STRING,
};

struct Value { 
    enum ValueType type;
    void *data; 
    size_t size; // for strings, arrays
    void (*destroy)(struct Value *); // free
    struct Value* (*copy)(struct Value *);
};

#endif // VALUE_H