// struct.c
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../include/struct.h"

// frees members and struct
int free_arg_struct(struct Arguments* arg1) { // what am I doing for commands that don't have key/value or have other params?
    free(arg1->key);
    free(arg1->value);
    free(arg1);
    return 0;
}

/* might move these command related functions at some point*/
// command -> enum mapping
static struct CommandOption command_table[] = {
    {"SET", CMD_SET},
    {"GET", CMD_GET},
    {"DEL", CMD_DEL},
    {"EXISTS", CMD_EXISTS},
};

/* Return enum representation of command string provided */
enum Command parse_command(const char* command_entered) {
    // for system agnosticism
    size_t n = sizeof(command_table) / sizeof(command_table[0]);

    for(size_t i = 0; i < n; i++) {
        if(strcmp(command_entered, command_table[i].name) == 0) {
            return command_table[i].cmd;
        } 
    }

    return CMD_UNKNOWN;
}

