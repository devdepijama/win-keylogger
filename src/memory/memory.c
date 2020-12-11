#include "memory.h"
#include "log/logger.h"
#include "settings/constants.h"

#include <stdlib.h>

static logger_t logger;

void memory_init(memory_parameters_s *parameters) {
    memory_parameters_s default_parameters = {
        .log_level = CONSTANT_LOG_LEVEL,
        .logName = "memory"
    };

    parameters = (!parameters) ? &default_parameters : parameters;
    logger_create(&logger, parameters->logName, parameters->log_level);
}

void * memory_alloc(unsigned int size, char *description) {
    void *result = malloc(size);
    if (!result) {
        logger_error(logger, "[addr:0x%X][size:%d bytes] Failed to allocate memory for %s. Out of memory, bro? :P", result, size, description);
        exit(-1);
    }

    logger_debug(logger, "[addr:0x%X][size:%d bytes] Allocated memory successfully for %s", result, size,  description);
    return result;
}
void memory_free(void *ptr) {
    logger_debug(logger, "[addr:0x%X] Freeing allocated memory...", ptr);
    return free(ptr);
}