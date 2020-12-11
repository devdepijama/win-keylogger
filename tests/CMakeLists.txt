include_directories (. ../src)

add_executable (
    TestRunner

    assertions/assertions.c
    test.c
)

target_link_libraries (TestRunner shared)