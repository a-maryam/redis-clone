/* driver.c: main of program */
#include "../include/parser.h"
#include "../include/read.h" 
#include "../include/struct.h"
#include "../include/hash_table.h"
#include "../include/value_functions.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t exit_flag = 0;

void int_handler(int signum) { 
    exit_flag = 1; 
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 
    sigaction(SIGINT, &sa, NULL);

    printf("**Toy Redis Started**\n Enter Commands:\n\n");
    int default_size = 16;
    struct hash_table* kv_store = create_table(default_size);

    while(!exit_flag) {
        char* input = read();

        if(input == NULL) {
            free(input);
            continue;
        }

        struct Arguments* a1 = parse(input);
        if(a1==NULL || input == NULL) {
            free_arg_struct(a1);
            free(input);
            a1=NULL;
            input = NULL;
            continue;
        }

        // Values inserted in hashtable, should be freed there
        switch(a1->command) {
            case STR_SET:
                struct Value* str_value = create_string_value(a1->value);
                insert(kv_store, a1->key, str_value);
                break;
            case STR_GET:
                get_value(kv_store, a1->key);
                break;
            case STR_DEL:
                delete_node(kv_store, a1->key);
                break;
            case KEY_EXISTS:
                node_exists(kv_store, a1->key);
                break;
            case CMD_UNKNOWN:
                printf("Unknown command.");
                break;
            default:
                printf("Unusual program behavior"); // this case should never occur.
                break; // exit program?
    }

    if(a1!=NULL) free_arg_struct(a1);
}

    free_hash_table(kv_store);
    return 0;
}