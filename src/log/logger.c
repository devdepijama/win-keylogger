#include "logger.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define PREFIX_SIZE 25

struct logger_s {
    char *name;
    int level;
};

// Do not change order. It matches the values of LOGGER_LEVEL_XXXXX
static char *level_name_by_level[] = {"ERROR", "WARN", "INFO", "DEBUG"};

static int logger_print(logger_t logger, unsigned int level, char *fmt, va_list args) {

    // Create a "prefixed" format string, by appending the log level and the log name
    char *prefixed_fmt = (char *) malloc(PREFIX_SIZE + (strlen(logger->name) + 1) + (strlen(fmt) + 1));
    char *log_level = level_name_by_level[level];
    sprintf(prefixed_fmt,"[%5s] - %s - %s \n", log_level, logger->name, fmt);

    vprintf(prefixed_fmt, args);

    free(prefixed_fmt);

    return LOGGER_E_SUCCESSFUL;
}

int logger_create(logger_t *destination, char *name, int level) {
    struct logger_s *ptrDestination;
    if (!name) return LOGGER_E_INVALID_NAME;

    *destination = (logger_t) malloc(sizeof(struct logger_s));
    ptrDestination = (struct logger_s*) *destination;

    ptrDestination->name = (char *) malloc(strlen(name) + 1);
    strcpy(ptrDestination->name, name);

    ptrDestination->level = level;

    return LOGGER_E_SUCCESSFUL;
}

int logger_info(logger_t logger, char *fmt, ...) {
    if (logger->level < LOGGER_LEVEL_INFO) return LOGGER_E_IGNORED;

    va_list args;
    va_start(args, fmt);
    logger_print(logger, LOGGER_LEVEL_INFO, fmt, args);
    va_end(args);

    return LOGGER_E_SUCCESSFUL;
}

int logger_warn(logger_t logger, char *fmt, ...) {
    if (logger->level < LOGGER_LEVEL_WARN) return LOGGER_E_IGNORED;

    va_list args;
    va_start(args, fmt);
    logger_print(logger, LOGGER_LEVEL_WARN, fmt, args);
    va_end(args);

    return LOGGER_E_SUCCESSFUL;
}

int logger_error(logger_t logger, char *fmt, ...) {
    if (logger->level < LOGGER_LEVEL_ERROR) return LOGGER_E_IGNORED;

    va_list args;
    va_start(args, fmt);
    logger_print(logger, LOGGER_LEVEL_ERROR, fmt, args);
    va_end(args);

    return LOGGER_E_SUCCESSFUL;
}

int logger_debug(logger_t logger, char *fmt, ...) {
    if (logger->level < LOGGER_LEVEL_DEBUG) return LOGGER_E_IGNORED;

    va_list args;
    va_start(args, fmt);
    logger_print(logger, LOGGER_LEVEL_DEBUG, fmt, args);
    va_end(args);

    return LOGGER_E_SUCCESSFUL;
}

void logger_destroy(logger_t logger) {
    free(logger->name);
    free(logger);
}