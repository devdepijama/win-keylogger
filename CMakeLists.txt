cmake_minimum_required(VERSION 3.17)
project(keylogger C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory (common)
add_subdirectory (hook)
add_subdirectory (src)
add_subdirectory (sharedmem-writer)
add_subdirectory (sharedmem-reader)
add_subdirectory (tests)