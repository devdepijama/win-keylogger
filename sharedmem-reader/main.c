#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <unistd.h>

#define SHARED_MEMORY_BUFFER_SIZE 256
#define SHARED_MEMORY_SIZE        sizeof(shared_memory_content_t)

typedef struct {
    unsigned int writer_index;
    unsigned int reader_index;
    char buffer[SHARED_MEMORY_BUFFER_SIZE];
}shared_memory_content_t;

char *sm_name = "MySharedMemory";

unsigned int read_shared_memory(void *shared_memory, char *buffer);

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
        SHARED_MEMORY_SIZE
    );

    if (shared_memory == NULL) {
        printf("Could not map view of file (%lX).\n", GetLastError());
        CloseHandle(shared_memory);
        return -1;
    }

    char read_buffer[SHARED_MEMORY_BUFFER_SIZE + 1];
    while(TRUE) {
        int read_bytes = read_shared_memory(shared_memory, read_buffer);
        if (read_bytes > 0) {
            read_buffer[read_bytes] = '\0';
            printf("%s", read_buffer);
        }
        usleep(50000);
    }

    UnmapViewOfFile(shared_memory);
    CloseHandle(handle_shared_memory);

    return 0;
}

unsigned int read_shared_memory(void *shared_memory, char *buffer) {
    shared_memory_content_t *content = (shared_memory_content_t *) shared_memory;
    unsigned int reader = content->reader_index;
    unsigned int writer = content->writer_index;
    unsigned int remaining, bytes_to_read;

    // Nothing new
    if (reader == writer) return 0;

    // Writer is in the front of reader
    if (writer > reader) {
        bytes_to_read = writer - reader;
        memcpy(buffer, content->buffer + reader, bytes_to_read);
        content->reader_index = writer;
        return bytes_to_read;
    }

    // Writer is behind
    remaining = SHARED_MEMORY_BUFFER_SIZE - reader;
    memcpy(buffer, content->buffer + reader, remaining);
    memcpy(buffer + remaining, content->buffer, writer);
    content->reader_index = writer;

    return (remaining + writer);
}
