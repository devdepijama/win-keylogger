#include "keyboard/listener.h"
#include "settings/constants.h"
#include "memory/shared.h"

#include <windows.h>
#include <stdlib.h>

static struct keyboard_listener_s {
    on_key_pressed_t key_pressed_callback;
    logger_t logger;
    HHOOK hook;
    shared_memory_t shared_memory;
} context;

int keyboard_listener_create(keyboard_listener_parameters_s *parameters) {
    context.key_pressed_callback = parameters->key_pressed_callback;
    context.logger = parameters->logger;
    context.hook = NULL;

    return KEYBOARD_LISTENER_E_SUCCESSFUL;
}

int keyboard_listener_start() {
    HINSTANCE hinstDLL = LoadLibrary(TEXT("libhook.dll"));

    logger_info(context.logger, "Installing keyboard hook");

    context.hook = SetWindowsHookEx(
        WH_KEYBOARD,
        (HOOKPROC) GetProcAddress(hinstDLL, "keyboard_hook_callback"),
        hinstDLL,
        0
    );

    if (!context.hook) {
        DWORD error = GetLastError();
        logger_error(context.logger, "Could not install hook: %d", error);
        return KEYBOARD_LISTENER_E_FAILED_TO_LISTEN;
    }

    if (SHAREDMEMORY_E_SUCCESS != shared_memory_instantiate(&(context.shared_memory))) {
        logger_error(context.logger, "Could not instantiate shared memory...");
        return KEYBOARD_LISTENER_E_FAILED_TO_LISTEN;
    }

    if (SHAREDMEMORY_E_SUCCESS != shared_memory_create(context.shared_memory)) {
        logger_error(context.logger, "Could not start shared memory...");
        return KEYBOARD_LISTENER_E_FAILED_TO_LISTEN;
    }

    return KEYBOARD_LISTENER_E_SUCCESSFUL;
}

int keyboard_listener_read(char *read_buffer, unsigned int *read_bytes) {
    if (SHAREDMEMORY_E_SUCCESS != shared_memory_read(context.shared_memory, read_buffer, read_bytes)) {
        return KEYBOARD_LISTENER_E_FAILED_TO_READ;
    }

    return KEYBOARD_LISTENER_E_SUCCESSFUL;
}

int keyboard_listener_destroy() {
    // Does nothing
}