#include <stdio.h>

#include "assertions/assertions.h"

#include "memory/memory.h"
#include "log/logger.h"

#ifdef CONSTANT_LOG_LEVEL
    #define CONSTANT_LOG_LEVEL LOGGER_LEVEL_DEBUG
#endif

void test_logger() {
    logger_t logger;

    printf("--- > Testing logger \n");

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_create(&logger, "myLoggerOnDebugLevel", LOGGER_LEVEL_DEBUG),
        "Failed to construct logger"
    );

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_info(logger, "Just a regular message on INFO level with argument %d", 2),
        "Failed to log on INFO level"
    );

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_warn(logger, "Just a regular message on WARN level"),
        "Failed to log on WARN level"
    );

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_error(logger, "Just a regular message on ERROR level"),
        "Failed to log on ERROR level"
    );

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_debug(logger, "Just a regular message on DEBUG level"),
        "Failed to log on DEBUG level"
    );

    logger_destroy(logger);

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_create(&logger, "myLoggerOnErrorLevel", LOGGER_LEVEL_ERROR),
        "Failed to construct logger on ERROR level"
    );

    assert_equals(
        LOGGER_E_IGNORED,
        logger_info(logger, "Just a regular message on INFO level with argument %d", 2),
        "Did not ignore an attempt to log on INFO level, even though log level is ERROR"
    );

    assert_equals(
        LOGGER_E_SUCCESSFUL,
        logger_error(logger, "Just a regular message on ERROR level"),
        "Failed to log on ERROR level"
    );
}

void test_memory() {
    printf("--- > Testing memory allocator \n");
    memory_parameters_s parameters = {
        .log_level = LOGGER_LEVEL_DEBUG,
        .logName = "memory"
    };
    memory_init(&parameters);

    int *ptr_to_int = memory_alloc(sizeof(int), "just a regular integer");
    *ptr_to_int = 10;

    assert_equals(10, *ptr_to_int, "Could not store value inside allocated memory");

    memory_free(ptr_to_int);
}

int main() {
    printf("Running tests \n");

    test_logger();
    test_memory();

    printf("Finished tests Successfully :)");
    return 0;
}
