#include <stdio.h>

#include "assertions/assertions.h"
#include "log/logger.h"

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

int main() {
    printf("Running tests \n");

    test_logger();

    printf("Finished tests Successfully :)");
    return 0;
}
