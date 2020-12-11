#include "logger.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define PREFIX_SIZE 25

struct logger_s {
    char *name;
};

static void logger_print(logger_t logger, char *log_level, char *fmt, va_list args) {
    // Create a "prefixed" format string, by appending the log level and the log name
    char *prefixed_fmt = (char *) malloc(PREFIX_SIZE + (strlen(fmt) + 1));
    sprintf(prefixed_fmt,"[%5s] - %s - %s \n", log_level, logger->name, fmt);

    vprintf(prefixed_fmt, args);

    free(prefixed_fmt);
}

int logger_create(logger_t *destination, char *name) {
    struct logger_s *ptrDestination;
    if (!name) return LOGGER_E_INVALID_NAME;

    *destination = (logger_t) malloc(sizeof(struct logger_s));
    ptrDestination = (struct logger_s*) *destination;

    ptrDestination->name = (char *) malloc(strlen(name) + 1);
    strcpy(ptrDestination->name, name);

    return LOGGER_E_SUCCESSFUL;
}

void logger_info(logger_t logger, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logger_print(logger, "INFO", fmt, args);
    va_end(args);
}

void logger_warn(logger_t logger, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logger_print(logger, "WARN", fmt, args);
    va_end(args);
}

void logger_error(logger_t logger, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logger_print(logger, "ERROR", fmt, args);
    va_end(args);
}

void logger_destroy(logger_t logger) {
    free(logger->name);
    free(logger);
}