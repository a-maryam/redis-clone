// commands.c
#include "../include/commands.h"
#include "../include/hash_table.h"
#include "../include/struct.h"

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
