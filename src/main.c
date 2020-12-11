#include <stdio.h>

#include "keyboard/listener.h"

void on_key_pressed_callback(char key) {
    printf("%c", key);
}

int main() {
    keyboard_listener_t keyboard_listener;
    keyboard_listener_create(&keyboard_listener, on_key_pressed_callback);
    printf("Did something");
    return 0;
}
