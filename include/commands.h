// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H
#include "hash_table.h"

char* get(struct hash_table* kv, char* key);
void set(struct hash_table* kv, struct Arguments* arg1);
void del(struct hash_table* kv, struct Arguments* arg1);
int exists(struct hash_table* kv, struct Arguments* arg1);

#endif