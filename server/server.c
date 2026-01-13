// server.c 
// socket programming to write http api running on local
// interface on top of kv store

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/commands.h"
#include "../src/hash_table.h"
#define PORT 8000 // fun port
//curl http://localhost:8000/

int main(int argc, char const* argv[]) {
    // accept connections 
    // parse HTTP 
    // translate requests
    // format HTTP responses
    // client = curl 

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
     

    while((bytes_read = read(new_socket, buffer, len_buffer)) > 0) {
        printf("Received request: %s\n", buffer);

        // find commands in http request

    }
    char* hello = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n"; 

    // with read will have to loop till end received
    send(new_socket, hello, strlen(hello), MSG_CONFIRM); // which flag? 

    // gotta loop, parse into args

    //read http request 

    close(new_socket);
    close(fd);
    return 0;

}