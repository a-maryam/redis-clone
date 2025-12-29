/*main.c 
currently contains parser, main, read, token to char func
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/struct.h"
#include "../include/parser.h"
#include "../include/commands.h"
// probably have to change from relative to whatever best practice is

// file organization: helper functions, and then in order of useage. 

struct Arguments* parse(char* input) {
    if(input==NULL) {
        return NULL;
    }

    // forget what ur supposed to do when you have a variable number 
    // of input tokens lol
    int tokens_allowed = 4;
    const char delimiters[] = " "; // might want to accommodate extra whitespace in future
    char* token;
    // array of token strings
    char** tokens_arr = malloc(tokens_allowed*sizeof(*tokens_arr));

    if(tokens_arr == NULL) {
        printf("Memory allocation for line failed\n");
        return NULL;
    }

    char** beg_arr = tokens_arr;
    token = strtok(input, delimiters);
    int i = 0;
    
    while(token!=NULL && i < tokens_allowed) {
        tokens_arr[i] = token;
        i++;
        token = strtok(NULL, delimiters); // get next token
    }

    if(i <= 1) {
        printf("Commands invalid");
        return NULL;
    }

    enum Command command1 = parse_command(beg_arr[0]);
    char* key1 = strdup(beg_arr[1]);
    char* value1 = (i > 2 ? strdup(beg_arr[2]) : NULL);
    
    struct Arguments *arg1 = malloc(sizeof(struct Arguments*));
    
    if(arg1 == NULL) {
        printf("Memory allocation for line failed\n");
        return NULL;
    }
    else { 
        arg1 -> command = command1;
        arg1 -> key = key1;
        arg1 -> value = value1;
    }

    free(tokens_arr); // function allocated and function freed
    free(input); // read allocated, caller freed (factory pattern)
    
    return arg1; // caller must free now.
}


