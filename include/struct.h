/* struct.h 
Purpose: so far hold structs used at the heart of the key-value store
*/

#ifndef STRUCT_H
#define STRUCT_H

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

/* maybe command things will live somewhere else later on*/
enum Command { // need more commands per data type
    STR_SET,
    STR_GET,
    STR_DEL,
    KEY_EXISTS, 
    CMD_UNKNOWN
};

struct CommandOption {
    const char *name;
    enum Command cmd;
};

struct Arguments {
    enum Command command;
    char *key; 
    char *value;
};

int free_arg_struct(struct Arguments* arg1);
enum Command parse_command(const char* command_entered); // will malloc for command / free struct should free / free is called from driver.


#endif // STRUCT_H