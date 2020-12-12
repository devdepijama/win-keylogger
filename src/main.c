#include <stdio.h>
#include <unistd.h>

#include "settings/constants.h"
#include "keyboard/listener.h"
#include "memory/memory.h"

static logger_t logger;

void on_key_pressed_callback(char key) {
    printf("%c", key);
}

void init_memory() {
    memory_parameters_s parameters;
    logger_create(&(parameters.logger), "memory", CONSTANT_LOG_LEVEL);
    memory_init(&parameters);
}

void init_keyboard_listener() {
    keyboard_listener_parameters_s parameters;
    logger_create(&(parameters.logger), "keyboard", CONSTANT_LOG_LEVEL);
    parameters.key_pressed_callback = on_key_pressed_callback;
    keyboard_listener_create(&parameters);
}

void init_logger() {
    logger_create(&logger, "app", CONSTANT_LOG_LEVEL);
}

void init() {
    init_memory();
    init_keyboard_listener();
    init_logger();
}

int main() {
    char input[100];
    init();

    if (KEYBOARD_LISTENER_E_SUCCESSFUL != keyboard_listener_start()) {
        logger_error(logger, "Could not start keyboard listener");
        return -1;
    }
    scanf("Press any key to uninstall WindowsHook: %s", &input);

    return 0;
}
