// arguments.h

#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include "../include/commands.h"

struct Arguments {
    enum Command command;
    char *key; 
    char *value;
};

int free_arg_struct(struct Arguments* arg1);

#endif