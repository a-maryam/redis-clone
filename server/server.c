// server.c
// TCP key-value server. Simple line protocol:
//   client sends:  "SSET key value\n"  or  "GET key\n"
//   server replies: "+OK\n"  /  "+<value>\n"  /  "-nil\n"  /  "-ERR ...\n"

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

#define PORT     8000
#define BUF_SIZE 1024

static const int default_size = 16;
static volatile sig_atomic_t exit_flag = 0;

static void int_handler(int signum) {
    (void)signum;
    const char *msg = "\n\nExiting KVSERVER...\n";
    write(1, msg, strlen(msg));
    exit_flag = 1;
}

static void send_str(int sock, const char *msg) {
    send(sock, msg, strlen(msg), 0);
}

static void handle_connection(int sock, struct hash_table **kv_store) {
    char buf[BUF_SIZE];
    ssize_t n;

    while ((n = read(sock, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';

        // strip trailing \r\n
        char *end = buf + n - 1;
        while (end >= buf && (*end == '\r' || *end == '\n'))
            *end-- = '\0';

        struct Arguments *args = parse(buf);
        if (!args) {
            send_str(sock, "-ERR parse error\n");
            continue;
        }

        switch (args->command) {
            case STR_SET: {
                struct Value *v = create_string_value(args->value);
                insert(kv_store, args->key, v);
                send_str(sock, "+OK\n");
                break;
            }
            case GET: {
                struct Value *v = get_value(*kv_store, args->key);
                if (v) {
                    char resp[BUF_SIZE];
                    snprintf(resp, sizeof(resp), "+%s\n", (char *)v->data);
                    send_str(sock, resp);
                } else {
                    send_str(sock, "-nil\n");
                }
                break;
            }
            case DEL:
                delete_node(*kv_store, args->key);
                send_str(sock, "+OK\n");
                break;
            case KEY_EXISTS:
                send_str(sock, node_exists(*kv_store, args->key) ? "+1\n" : "+0\n");
                break;
            case CMD_UNKNOWN:
            default:
                send_str(sock, "-ERR unknown command\n");
                break;
        }
        free_arg_struct(args);
    }
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    int fd, opt = 1;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { perror("socket"); return 1; }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port        = htons(PORT),
    };
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    if (listen(fd, 128) < 0) { perror("listen"); return 1; }

    printf("Listening on port %d...\n", PORT);

    struct hash_table *kv_store = create_table(default_size);
    socklen_t addr_len = sizeof(addr);

    while (!exit_flag) {
        int client = accept(fd, (struct sockaddr *)&addr, &addr_len);
        if (client < 0) {
            if (!exit_flag) perror("accept");
            break;
        }
        handle_connection(client, &kv_store);
        close(client);
    }

    free_hash_table(kv_store);
    close(fd);
    return 0;
}
