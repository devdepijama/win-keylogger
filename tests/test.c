#include <stdio.h>

#include "assertions/assertions.h"

#include "memory/memory.h"
#include "log/logger.h"

#ifdef CONSTANT_LOG_LEVEL
    #define CONSTANT_LOG_LEVEL LOGGER_LEVEL_DEBUG
#endif

static logger_t logger_keyboard_listener;
static logger_t logger_tests;
static logger_t logger_memory;

static void init();
static void test_logger();
static void test_memory();
static void test_keyboard_listener();

int main() {
    init();

    logger_info(logger_tests,"Running tests...");

    test_logger();
    test_memory();
    test_keyboard_listener();

    logger_info(logger_tests,"Finished tests Successfully :)");
    return 0;
}

static void init() {
    logger_create(&logger_keyboard_listener, "key-interceptor", LOGGER_LEVEL_DEBUG);
    logger_create(&logger_tests, "tests", LOGGER_LEVEL_DEBUG);
    logger_create(&logger_memory, "memory", LOGGER_LEVEL_DEBUG);

    logger_info(logger_tests, "Setting tests up...");

    memory_parameters_s parameters = {
        .logger = logger_memory
    };
    memory_init(&parameters);
}

static void test_logger() {
    logger_t logger;

    logger_info(logger_tests, "Testing Logger...");

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

static void test_memory() {
    logger_info(logger_tests,"Testing memory allocator");

    int *ptr_to_int = memory_alloc(sizeof(int), "a regular integer");
    *ptr_to_int = 10;

    assert_equals(10, *ptr_to_int, "Could not store value inside allocated memory");

    memory_free(ptr_to_int, "a regular integer");
}

static void test_keyboard_listener() {
    logger_t logger;

}
