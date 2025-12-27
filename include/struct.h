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
    ValueType value;
    union {
        float f;
        char c; 
        double d;
        int i;
        int *arr_ptr; 
        int *char_ptr;
        // create structs for other data types later
        // lists, heaps, trees...
    } data;
};
/* maybe command things will live somewhere else later on*/
enum Command {
    CMD_SET,
    CMD_GET,
    CMD_DEL,
    CMD_EXISTS, 
    CMD_UNKNOWN
};

struct CommandOption {
    const char *name;
    struct Command cmd;
}

struct Arguments {
    enum Command command;
    char *key; 
    char *value;
};

int free_arg_struct(struct Arguments* arg1);
enum Command* parse_command(const char* command_entered) // will malloc for command / free struct should free / free is called from driver.

#endif // STRUCT_H