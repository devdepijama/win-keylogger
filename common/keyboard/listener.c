#include "keyboard/listener.h"
#include "settings/constants.h"

#include <windows.h>
#include <stdlib.h>

static struct keyboard_listener_s {
    on_key_pressed_t key_pressed_callback;
    logger_t logger;
    HHOOK hook;
} context;

static char toChar(WPARAM value) {
    BYTE keyboard_state[256];
    GetKeyboardState(keyboard_state);
    WORD w;
    UINT scan=0;

    if (value == VK_RETURN) return '\n';
    if (value == VK_SPACE) return ' ';
    ToAscii(value, scan, keyboard_state, &w, 0);
    return ((char) w);
}

LRESULT CALLBACK hook_callback(int ncode, WPARAM wparam, LPARAM lparam) {

    if (((DWORD)lparam & 0x40000000) && (HC_ACTION == ncode)) {
        if ((wparam == VK_SPACE) || (wparam == VK_RETURN) || (wparam >= 0x2f ) && (wparam <= 0x100)) {
            context.key_pressed_callback(toChar(wparam));
        }
    }

    return CallNextHookEx(context.hook, ncode, wparam, lparam);
}

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

    return KEYBOARD_LISTENER_E_SUCCESSFUL;
}

int keyboard_listener_destroy() {
    // Does nothing
}