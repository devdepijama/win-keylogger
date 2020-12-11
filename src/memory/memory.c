#include "memory.h"
#include "log/logger.h"

#include <stdlib.h>

void * memory_alloc(unsigned int size) {
    return malloc(size);
}
void memory_free(void *ptr) {
    return free(ptr);
}