/*main.c 
currently contains parser, main, read, token to char func
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/struct.h"
#include "../include/parser.h"
#include "../include/commands.h"
#include "../include/input.h"
#include "../include/hash_table.h"
#include "../include/tests.h"
// probably have to change from relative to whatever best practice is

// file organization: helper functions, and then in order of useage. 

static char* token_to_char_arr(char* ptr) { // function allocates temp/beg: caller frees
    if(ptr == NULL) return NULL;
    // mem allocated
    int len = 50; // totally open to change this later. 
    char* temp = malloc(len * sizeof(*temp));
    if(temp == NULL) {
        printf("Memory allocation in token to char arr has failed.");
        return NULL;
    }

    char* beg = temp;
    
    int i = 0; 
    while(*ptr != '\0' && i < len - 1) {
        printf("%c", *ptr);
        *temp++ = *ptr++;
        i++;
    }
    *temp = '\0';

    printf("\nend of one char arr making run.\n");
    return beg; // must free as well 
}

// frees members and struct
static int free_arg_struct(struct Arguments* arg1) {
    free(arg1->key);
    free(arg1->value);
    free(arg1);
    return 0;
}

char* read() {
    int line_length = 100;
    char* line = malloc(line_length * sizeof(*line));

    if(line == NULL) {
        printf("Memory allocation for line failed\n");
        return NULL;
    }

    printf("**Toy Redis Started**\n Enter Commands:\n");
    // will need to implement error handling for invalid inputs
    if(fgets(line, line_length, stdin) != NULL) {
        printf("Entered: %s", line);
    } 
    else {
        printf("Error reading input.");
    }
    return line; // seems correct
} 

int parse(char* input) {
    // forget what ur supposed to do when you have a variable number 
    // of input tokens lol
    int tokens_allowed = 4;
    const char delimiters[] = " "; // might want to accommodate extra whitespace in future
    char* token;
    // array of token strings
    char** tokens_arr = malloc(tokens_allowed*sizeof(*tokens_arr));

    if(tokens_arr == NULL) {
        printf("Memory allocation for line failed\n");
        return -1;
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
        return -1;
    }

    // need tokens, and input if passing along. 
    // can just copy to new vars and pass. easier
    char* key1 = token_to_char_arr(beg_arr[1]);
    char* value1 = (i > 2 ? token_to_char_arr(beg_arr[2]) : NULL);
    
    struct Arguments *arg1 = malloc(sizeof(struct Arguments));
    
    if(arg1 == NULL) {
        printf("Memory allocation for line failed\n");
        return -1;
    }
    else { 
        arg1 -> key = key1;
        arg1 -> value = value1;
    }

    test_kv_insert(arg1);

    /*struct hash_table* kv_store = create_table();

    if(strcmp(beg_arr[0], "GET")==0) { 
        get(kv_store, arg1);
    }
    else if(strcmp(beg_arr[0], "SET")==0) {
        set(kv_store, arg1);
    }
    else if(strcmp(beg_arr[0], "DEL")==0) {
        del(kv_store, arg1);
    }
    else if(strcmp(beg_arr[0], "EXISTS")==0) {
        exists(kv_store, arg1);
    }*/
    free(tokens_arr); // function allocated and function freed
     
    // frees token_to_char_arr allocated mem
    free_arg_struct(arg1); // caller allocated and caller freed / container freeing.
    free(input); // read allocated, caller freed (factory pattern)
    // tokens from input were put into new buffers anyhow.
    return 0; // need my hash table...before i can write the functions
}

int test_kv_insert(struct Arguments* arg1) {
    struct hash_table* kv_store = create_table();
    set(kv_store, arg1);
    return 0;
}

/* COMMANDS */
// kv assumed initialized. should be in command loop. 
int set(struct hash_table* kv, struct Arguments* arg1) {
    insert(kv, arg1);
    return 0;
}

int get(struct hash_table* kv, struct Arguments* arg1) {
    
    return 0;
}

int del(struct hash_table* kv, struct Arguments* arg1) {
   
    return 0;
}

int exists(struct hash_table* kv, struct Arguments* arg1) {
    
    return 0;
}

int main(void) {
    parse(read());
    return 0;
}