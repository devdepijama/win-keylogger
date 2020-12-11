include_directories (${KEYLOGGER_SOURCE_DIR}/src)

add_executable (
    TestRunner

    test.c
    test_logger.c
)

target_link_libraries (TestRunner shared)