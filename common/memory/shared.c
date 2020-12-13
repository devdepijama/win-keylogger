#include "memory/shared.h"
#include "memory/memory.h"

#include <string.h>
#include <windows.h>

#define INSTANCE_CREATION_REASON "shared memory instance"
#define READ_BUFFER_CREATION_REASON "shared memory read buffer"

struct shared_memory_s {
    char *name;
    unsigned int size;
    logger_t logger;
    HANDLE handle_shared_memory;
    void *shared_memory;
    void *read_buffer;
    on_published_content_t read_callback;
};

int shared_memory_instantiate(shared_memory_t *instance, shared_memory_parameters_t parameters) {
    *instance = memory_alloc(sizeof(struct shared_memory_s), INSTANCE_CREATION_REASON);
    (*instance)->name = parameters.name;
    (*instance)->size = parameters.size;
    (*instance)->logger = parameters.logger;
    (*instance)->read_buffer = memory_alloc(parameters.size, READ_BUFFER_CREATION_REASON);

    return SHAREDMEMORY_E_SUCCESS;
}

int shared_memory_create(shared_memory_t instance) {
    instance->handle_shared_memory = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            instance->size,          // maximum object size (low-order DWORD)
            instance->name           // name of mapping object
    );

    if (NULL == instance->handle_shared_memory) {
        logger_error(instance->logger, "Could not create file mapping object (%lX).\n", GetLastError());
        return SHAREDMEMORY_E_COULD_NOT_CREATE;
    }

    instance->shared_memory = MapViewOfFile(
        instance->handle_shared_memory,  // handle to map object
        FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        instance->size
    );

    if (NULL == instance->shared_memory) {
        logger_error(instance->logger,"Could not map view of file (%lX).\n", GetLastError());
        CloseHandle(instance->handle_shared_memory);
        return SHAREDMEMORY_E_COULD_NOT_CREATE;
    }

    return SHAREDMEMORY_E_SUCCESS;
}

int shared_memory_write(shared_memory_t instance, void *content, unsigned int size) {
    CopyMemory((PVOID) instance->shared_memory, content, size);
    return SHAREDMEMORY_E_SUCCESS;
}

int shared_memory_attach_listener(shared_memory_t instance, on_published_content_t callback) {
    instance->read_callback = callback;
    return SHAREDMEMORY_E_SUCCESS;
}

int shared_memory_read(shared_memory_t instance) {
    instance->read_callback(instance->shared_memory, instance->size);
    return SHAREDMEMORY_E_SUCCESS;
}

int shared_memory_free(shared_memory_t instance) {
    UnmapViewOfFile(instance->shared_memory);
    CloseHandle(instance->handle_shared_memory);
    free(instance->read_buffer);
    free(instance);
    return SHAREDMEMORY_E_SUCCESS;
}