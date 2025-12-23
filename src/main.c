#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/struct.h"
// probably have to change from relative to whatever best practice is

int* read() {
    char line[100];
    printf("**Toy Redis Started**\n Enter Commands:\n");
    // will need to implement error handling for invalid inputs
    if(fgets(line, sizeof(line), stdin) != NULL) {
        printf("Entered: %s", line);
    } 
    else {
        printf("Error reading input.");
    }
    return line;
} // need to free...parse will free

int parse(char[] input) {
    // strtok should go till null character in line, right?
    // forget what ur supposed to do when you have a variable number 
    // of input tokens lol
    int tokens_allowed = 4;
    const char delimiters[] = " "; // might want to accommodate extra whitespace in future
    char *token;
    char *tokens_arr[tokens_allowed]; // gonna need checks, expect only 3 tokens atm
    token = strtok(input, delimiters);

    int i = 0;
    
    while(token!=NULL && i < tokens_allowed) {
        tokens_arr[i++] = token; // store ptr
        token = strtok(NULL, delimiters); // get next token
    }

    printf("Tokens\n");

    for(int j = 0; j < i; j++) {
        printf("Token %d: %s\n", j+1, tokens_arr[j]);
    }
    // need tokens, and input if passing along. 
    // can just copy to new vars and pass. easier

    if(strcmp(tokens_arr[0], "GET")==0) {
        
        get()
    }
    return 0; // need my hash table...before i can write the functions
}

set() {

}

get() {

}

del() {

}

int main(void) {
    parse(read());
    return 0;
}