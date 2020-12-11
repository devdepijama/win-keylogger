#include "listener.h"

struct keyboard_listener_s {
    on_key_pressed_t key_pressed_callback;
};

int keyboard_listener_create(keyboard_listener_t *destination, on_key_pressed_t on_key_pressed) {

}

int keyboard_listener_start(keyboard_listener_t *instance) {

}

int keyboard_listener_destroy(keyboard_listener_t *instance) {

}