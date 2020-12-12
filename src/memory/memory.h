#ifndef H_MEMORY
#define H_MEMORY

#include "log/logger.h"

typedef struct {
    logger_t logger;
} memory_parameters_s;

void memory_init(memory_parameters_s *parameters);
void * memory_alloc(unsigned int size, char *description);
void memory_free(void *ptr, char *description);

#endif