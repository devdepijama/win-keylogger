#include "keyboard/listener.h"
#include "memory/memory.h"

#define DESCRIPTION_OF_INSTANCE "instance of keyboard listener"

struct keyboard_listener_s {
    on_key_pressed_t key_pressed_callback;
};

int keyboard_listener_create(keyboard_listener_t *destination, keyboard_listener_parameters_s *parameters) {
    struct keyboard_listener_s *this = memory_alloc(sizeof(struct keyboard_listener_s), DESCRIPTION_OF_INSTANCE);
    this->key_pressed_callback = parameters->key_pressed_callback;

    *destination = this;

    return KEYBOARD_LISTENER_E_SUCCESSFUL;
}

int keyboard_listener_start(keyboard_listener_t *instance) {

}

int keyboard_listener_destroy(keyboard_listener_t *instance) {
    memory_free(instance, DESCRIPTION_OF_INSTANCE);
}