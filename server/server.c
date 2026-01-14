// server.c 
// socket programming to write http api running on local
// interface on top of kv store

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/commands.h"
#include "../include/hash_table.h"
#include "../include/parser.h"
#include "../include/arguments.h"
#include "../include/value_functions.h"
#define PORT 8000 // fun port
//curl http://localhost:8000/

const int default_size = 16; 

volatile sig_atomic_t exit_flag = 0;

// print statements here have potential to cause deadlocks. 
void int_handler(int signum) { 
    const char* exit_message = "\n\nExiting KVSERVER...\n";
    size_t nbytes = strlen(exit_message);
    write(1, exit_message, nbytes);
    // doesn't matter if write is successful - no checks. 
    exit_flag = 1; 
}

int main(int argc, char const* argv[]) {
    struct sigaction sa = {0};
    sa.sa_handler = int_handler; // exit on Ctrl+C
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // default behavior of signal handling
    sigaction(SIGINT, &sa, NULL); // register action

    int fd;
    int new_socket;
    int opt = 1;

    // IPv4, TCP Protocal stream socket, 
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed.\n");
        exit(EXIT_FAILURE);
    }

    // configure socket behavior: forcing socket to bind to 
    // address and port if in use and allows myltiple sockets
    // to bind to the same address and port -
    // actually may not need this behavior unless extending project
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    socklen_t len_addr = sizeof(address);
    address.sin_family = AF_INET;
    // server can accept any connections on an ip address of machine
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(PORT); // convert to network byte order

    if(bind(fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }

    if(listen(fd, 3) < 0) { // second arg = number of allowed pending connections
        perror("Listen failed\n");
         exit(EXIT_FAILURE);
    }

    printf("Listening on port 8000...\n");

    if((new_socket = accept(fd, (struct sockaddr*)&address, &len_addr)) < 0) {
        perror("Accept failed\n");
        exit(EXIT_FAILURE);
    }
    int len_buffer = 1024;
    char buffer[len_buffer] = {};
    ssize_t bytes_read;
    struct hash_table* kv_store = create_table(default_size);

    // assuming full request arrives in read (later: use content-length in header)
    while((bytes_read = read(new_socket, buffer, len_buffer)) > 0) {
        printf("Received request: %s\n", buffer);

        char* body = strstr(buffer, "\r\n\r\n");

        if(!body) {
            continue;
        }
        body+=4; // skip "\r\n\r\n"

        struct Arguments* a1 = parse(body);

        if(!a1) {
            free(a1);
            continue;
        }

        switch(a1->command) {
            case STR_SET:
                // owned by hashtable unless failure makes another function responsible
                struct Value* str_value = create_string_value(a1->value); 
                insert(&kv_store, a1->key, str_value);
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
                break; 
        }
        free_arg_struct(a1);
    }
    free_hash_table(kv_store);
    // need sighandler
    char* hello = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n"; 

    // with read will have to loop till end received
    send(new_socket, hello, strlen(hello), MSG_CONFIRM); // which flag? 

    close(new_socket);
    close(fd);
    return 0;

}