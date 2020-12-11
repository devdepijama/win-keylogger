#ifndef H_LOGGER
#define H_LOGGER

#define LOGGER_E_SUCCESSFUL     0
#define LOGGER_E_INVALID_NAME   1

typedef struct logger_s* logger_t;

int logger_create(logger_t *destination, char *name);

void logger_info(logger_t logger, char *fmt, ...);
void logger_warn(logger_t logger, char *fmt, ...);
void logger_error(logger_t logger, char *fmt, ...);

void logger_destroy(logger_t logger);

#endif