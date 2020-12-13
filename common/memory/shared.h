#ifndef H_SHAREDMEMORY
#define H_SHAREDMEMORY

#include "log/logger.h"

#define SHAREDMEMORY_E_SUCCESS              0
#define SHAREDMEMORY_E_COULD_NOT_CREATE     1

typedef struct shared_memory_s* shared_memory_t;
typedef void (*on_published_content_t)(void *, unsigned int);

typedef struct {
    char *name;
    unsigned int size;
    logger_t logger;
} shared_memory_parameters_t;

int shared_memory_instantiate(shared_memory_t *instance, shared_memory_parameters_t parameters);

int shared_memory_create(shared_memory_t instance);
int shared_memory_write(shared_memory_t instance, void *content, unsigned int size);

int shared_memory_attach_listener(shared_memory_t instance, on_published_content_t callback);
int shared_memory_read(shared_memory_t instance);

int shared_memory_free(shared_memory_t instance);

#endif