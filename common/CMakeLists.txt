add_library (
    common
    SHARED

    keyboard/listener.c
    log/logger.c
    memory/memory.c
    memory/shared.c
)
target_include_directories(common PRIVATE .)