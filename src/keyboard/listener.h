#ifndef H_LISTENER
#define H_LISTENER

#define KEYBOARD_LISTENER_E_SUCCESSFUL 0

typedef struct keyboard_listener_s* keyboard_listener_t;

typedef void (*on_key_pressed_t)(char);
typedef struct {
    on_key_pressed_t key_pressed_callback;
} keyboard_listener_parameters_s;

int keyboard_listener_create(keyboard_listener_t *destination, keyboard_listener_parameters_s *parameters);
int keyboard_listener_start(keyboard_listener_t *instance);
int keyboard_listener_destroy(keyboard_listener_t *instance);


#endif