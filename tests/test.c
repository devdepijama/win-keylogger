#include <stdio.h>

#include "assertions/assertions.h"
#include "log/logger.h"

void test_logger() {
    logger_t logger;

    printf("--- > Testing logger \n");

    assert_equals(LOGGER_E_SUCCESSFUL, logger_create(&logger, "myLogger"), "Failed to construct logger");
    logger_info(logger, "Just a regular message on INFO level with argument %d", 2);
    logger_warn(logger, "Just a regular message on WARN level");
    logger_error(logger, "Just a regular message on ERROR level");

    logger_destroy(logger);
}

int main() {
    printf("Running tests \n");

    test_logger();

    printf("Finished tests Successfully :)");
    return 0;
}
