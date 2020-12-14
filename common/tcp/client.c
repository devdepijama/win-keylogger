#include "tcp/client.h"
#include "log/logger.h"
#include "memory/memory.h"
#include "settings/constants.h"

#include <stdio.h>
#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define DESCRIPTION_INSTANCE "tcpclient instance object"

struct tcp_client_s {
    WSADATA wsa;
    SOCKET socket;
    logger_t logger;
};

static logger_t logger = NULL;

int tcpclient_create(tcp_client_t *instance) {
    if (NULL == logger) {
        logger_create(&logger, "tcpclient", CONSTANT_LOG_LEVEL);
    }

    *instance = memory_alloc(sizeof(struct tcp_client_s), DESCRIPTION_INSTANCE);
    (*instance)->logger = logger;

    return TCPCLIENT_E_SUCCESSFUL;
}

int tcpclient_open(tcp_client_t instance, char *host, unsigned short port) {
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(host);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (WSAStartup(MAKEWORD(2,2), &(instance->wsa))) {
        logger_error(instance->logger, "Could not load WSA lib 2.2. Error %X", WSAGetLastError());
        return TCPCLIENT_E_COULD_NOT_OPEN;
    }

    instance->socket = socket(AF_INET , SOCK_STREAM , 0 );
    if(INVALID_SOCKET == instance->socket) {
        logger_error(instance->logger, "Could not create socket. Error %X", WSAGetLastError());
        return TCPCLIENT_E_COULD_NOT_OPEN;
    }

    if (connect(instance->socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        logger_error(instance->logger, "Could not connect to destination");
        return TCPCLIENT_E_COULD_NOT_OPEN;
    }

    return TCPCLIENT_E_SUCCESSFUL;
}

int tcpclient_send(tcp_client_t instance, void *data, unsigned int data_size) {
    if (send(instance->socket, data, data_size, 0) < 0) {
        logger_error(instance->logger, "Could not send data to destination...");
        return TCPCLIENT_E_COULD_NOT_SEND;
    }

    return TCPCLIENT_E_SUCCESSFUL;
}

int tcpclient_free(tcp_client_t instance) {
    return TCPCLIENT_E_SUCCESSFUL;
}