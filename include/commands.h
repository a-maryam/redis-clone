// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

enum Command { // need more commands per data type
    STR_SET,
    GET,
    DEL,
    KEY_EXISTS, 
    CMD_UNKNOWN
};

struct CommandOption {
    const char *name;
    enum Command cmd;
};

enum Command parse_command(const char* command_entered); // will malloc for command / free struct should free / free is called from driver.

#endif 