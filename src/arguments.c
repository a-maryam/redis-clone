// struct.c
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../include/arguments.h"

// frees members and struct
int free_arg_struct(struct Arguments* arg1) { 
    free(arg1->key);
    free(arg1->value);
    free(arg1);
    return 0;
}

