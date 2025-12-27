/* struct.h 
Purpose: so far hold structs used at the heart of the key-value store
*/
#ifndef STRUCT_H
#define STRUCT_H

// key will be char[] 

typedef enum {
    VALUE_FLOAT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_INT,
    VALUE_INT_PTR,
    VALUE_CHAR_PTR
} ValueType;

// union must hold pointers.
struct Value {
    ValueType value;
    union {
        float f;
        char c; 
        double d;
        int i;
        int *arr_ptr; // will be dynamically allocated and live on heap
        int *char_ptr;
        // create structs for other data types later
        // lists, heaps, trees...
    } data;
};

// dunno typedef didn't seem to be working. circble back
struct Arguments {
    char *key; 
    char *value;
};

int free_arg_struct(struct Arguments* arg1);

#endif // STRUCT_H