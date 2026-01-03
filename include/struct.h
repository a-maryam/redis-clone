/* struct.h 
Purpose: so far hold structs used at the heart of the key-value store
*/
#ifndef STRUCT_H
#define STRUCT_H

enum ValueType {
    VALUE_FLOAT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_INT,
    VALUE_INT_PTR,
    VALUE_CHAR_PTR
};

// union must hold pointers.
struct Value {
    enum ValueType type;
    void *data;
    size_t size; // for strings, arrays
    void (*destroy)(void *); // free
    void (*copy)(void *); // for insert
};

/* maybe command things will live somewhere else later on*/
enum Command { // need more commands per data type -- refactor i think
    CMD_SET,
    CMD_GET,
    CMD_DEL,
    CMD_EXISTS, 
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