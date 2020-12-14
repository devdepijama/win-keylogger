#ifndef H_TCP_CLIENT
#define H_TCP_CLIENT

#define TCPCLIENT_E_SUCCESSFUL          0
#define TCPCLIENT_E_COULD_NOT_CREATE    1
#define TCPCLIENT_E_COULD_NOT_OPEN      2
#define TCPCLIENT_E_COULD_NOT_SEND      3

typedef struct tcp_client_s* tcp_client_t;

int tcpclient_create(tcp_client_t *instance);

int tcpclient_open(tcp_client_t instance, char *host, unsigned short port);
int tcpclient_send(tcp_client_t instance, void *data, unsigned int data_size);

int tcpclient_free(tcp_client_t instance);

#endif