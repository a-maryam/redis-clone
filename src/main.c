/*main.c 
currently contains parser, main, read, token to char func
*/
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

char* token_to_char_arr(char* ptr) {
    if(ptr == null) return null;
    // mem allocated
    char[] temp = new char[50];
    int i = 0; 
    while(*ptr != '\0' && i < 50) {
        printf("%c", *ptr);
        temp[i++] = *ptr;
        ptr++;
    }
    return temp;

}

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
    free(delimiters);

    printf("Tokens\n");

    for(int j = 0; j < i; j++) {
        printf("Token %d: %s\n", j+1, tokens_arr[j]);
    }

    if(i <= 1) {
        printf("Commands invalid");
        return null;
    }
    // need tokens, and input if passing along. 
    // can just copy to new vars and pass. easier
    char key[] = token_to_char_arr(tokens_arr[1]);
    char value[] = (i > 2 ? token_to_char_arr(tokens_arr[2]) : null)

    Arguments arg1 = {key, value};

    if(strcmp(tokens_arr[0], "GET")==0) { 
        get(arg1);
    }
    else if(strcmp(tokens_arr[0], "SET")==0) {
        set(arg1);
    }
    else if(strcmp(tokens_arr[0], "DEL")==0) {
        del(arg1);
    }
    else if(strcmp(tokens_arr[0], "EXISTS")==0) {
        exists(arg1);
    }

    free(tokens_arr);
    free(token);

    return 0; // need my hash table...before i can write the functions
}

int set(Arguments arg1) {
    return 0;
}

get(Arguments arg1) {
    return 0;
}

del(Arguments arg1) {
    return 0;
}

exists(Arguments arg1) {
    return 0;
}

int main(void) {
    parse(read());
    return 0;
}