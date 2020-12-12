#ifndef H_LISTENER
#define H_LISTENER

#include "log/logger.h"

#define KEYBOARD_LISTENER_E_SUCCESSFUL 0
#define KEYBOARD_LISTENER_E_FAILED_TO_LISTEN 1

typedef void (*on_key_pressed_t)(char);
typedef struct {
    on_key_pressed_t key_pressed_callback;
    logger_t logger;
} keyboard_listener_parameters_s;

int keyboard_listener_create(keyboard_listener_parameters_s *parameters);
int keyboard_listener_start();
int keyboard_listener_destroy();

#endif