#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <unistd.h>

#define MEMORY_SIZE 256
char *sm_name = "MySharedMemory";

int main()
{
    HANDLE handle_shared_memory;
    void *shared_memory;

    handle_shared_memory = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        sm_name                // name of mapping object
    );

    if (handle_shared_memory == NULL) {
        printf("Could not open file mapping object (%lX).\n", GetLastError());
        return -1;
    }

    shared_memory = MapViewOfFile(
        handle_shared_memory,               // handle to map object
        FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        MEMORY_SIZE
    );

    if (shared_memory == NULL) {
        printf("Could not map view of file (%lX).\n", GetLastError());
        CloseHandle(shared_memory);
        return -1;
    }

    for(int i = 0; i < 100; i++) {
        printf("Read from shared memory: \"%s\" \n", shared_memory);
        usleep(300000);
    }

    UnmapViewOfFile(shared_memory);
    CloseHandle(handle_shared_memory);

    return 0;
}