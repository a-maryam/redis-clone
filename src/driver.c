/* driver.c: main of program*/
#include "../include/parser.h"
#include "../include/read.h" 
#include "../include/struct.h"
#include "../include/hash_table.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t exit_flag = 0;

void int_handler(int signum) { // probably can remove signum
    exit_flag = 1; 
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 
    sigaction(SIGINT, &sa, NULL);

    printf("**Toy Redis Started**\n Enter Commands:\n");
    struct hash_table* kv_store = create_table();

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

        switch(a1->command) {
            case CMD_SET:
                insert(kv_store, a1);
                break;
            case CMD_GET:
                get_value(kv_store, a1->key);
                break;
            case CMD_DEL:
                delete_node(kv_store, a1->key);
                break;
            case CMD_EXISTS:
                node_exists(kv_store, a1->key);
                break;
            case CMD_UNKNOWN:
                printf("Unknown command."); // should likely exit program.
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