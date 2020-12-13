#include <windows.h>
#include <stdio.h>

#define MEMORY_SIZE 256
char *sm_name = "MySharedMemory";
char *sm_message = "Message from first process.";

int main()
{
    HANDLE handle_shared_memory;
    void *shared_memory;

    handle_shared_memory = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        MEMORY_SIZE,             // maximum object size (low-order DWORD)
        sm_name                  // name of mapping object
    );

    if (handle_shared_memory == NULL) {
        printf("Could not create file mapping object (%lX).\n", GetLastError());
        return -1;
    }

    shared_memory = MapViewOfFile(
        handle_shared_memory,  // handle to map object
        FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        MEMORY_SIZE
    );

    if (shared_memory == NULL) {
        printf("Could not map view of file (%lX).\n", GetLastError());
        CloseHandle(handle_shared_memory);
        return -1;
    }

    CopyMemory((PVOID) shared_memory, sm_message, strlen(sm_message) + 1);
    scanf("%d");

    UnmapViewOfFile(shared_memory);
    CloseHandle(handle_shared_memory);

    return 0;
}