/*main.c 
currently contains parser, main, read, token to char func
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/struct.h"
#include "../include/parser.h"
//#include "../include/commands.h"

// probably have to change from relative to whatever best practice is

/* owns token_arr and input (from read function) */
struct Arguments* parse(char* input) {
    if(input==NULL) {
        free(input);
        input = NULL;
        return NULL;
    }

    int tokens_allowed = 4;
    const char delimiters[] = " "; // might want to accommodate extra whitespace in future
    char* token;
    // array of token strings
    char** tokens_arr = malloc(tokens_allowed*sizeof(*tokens_arr));

    if(tokens_arr == NULL) {
        free(tokens_arr);
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
        free(tokens_arr);
        printf("Commands invalid");
        return NULL;
    }

    enum Command command1 = parse_command(beg_arr[0]);
    char* key1 = strdup(beg_arr[1]);
    char* value1 = (i > 2 ? strdup(beg_arr[2]) : NULL);
    
    struct Arguments *arg1 = malloc(sizeof(*arg1));
    
    if(arg1 == NULL) {
        free(tokens_arr);
        free_arg_struct(arg1);
        printf("Memory allocation for line failed\n");
        return NULL;
    }
    else { 
        arg1 -> command = command1;
        arg1 -> key = key1;
        arg1 -> value = value1;
    }

    // function allocated and function freed
    free(tokens_arr);
    free(input); // read allocated, caller freed (factory pattern)
    
    return arg1; // caller must free now.
}


