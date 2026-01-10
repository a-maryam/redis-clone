// commands.c
#include "../include/commands.h"
#include <string.h>

// command -> enum mapping
static struct CommandOption command_table[] = {
    {"SSET", STR_SET},
    {"SGET", STR_GET},
    {"SDEL", STR_DEL},
    {"EXISTS", KEY_EXISTS},
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

