#ifndef H_LISTENER
#define H_LISTENER

#include "log/logger.h"

#define KEYBOARD_LISTENER_E_SUCCESSFUL 0
#define KEYBOARD_LISTENER_E_FAILED_TO_CREATE 1
#define KEYBOARD_LISTENER_E_FAILED_TO_LISTEN 2
#define KEYBOARD_LISTENER_E_FAILED_TO_READ   3

int keyboard_listener_create();
int keyboard_listener_start();
int keyboard_listener_read(char *read_buffer, unsigned int *read_bytes);
int keyboard_listener_destroy();

#endif