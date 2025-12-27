/* driver.c: main of program*/
#include "../include/parser.h"
#include "../include/read.h"
#include "../include/struct.h"

int main(void) {
    struct Arguments* a1 = parse(read());

    // command loop logic: 
    
    /*if(strcmp(beg_arr[0], "GET")==0) { 
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

    // have to rewrite Arguments struct

    free_arg_struct(a1);
    return 0;
}