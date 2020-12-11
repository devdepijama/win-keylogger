add_library (
    shared

    keyboard/listener.c
    log/logger.c
    memory/memory.c
)
target_include_directories(shared PRIVATE .)

add_executable (app main.c)
target_include_directories(app PRIVATE .)
target_link_libraries (app shared)