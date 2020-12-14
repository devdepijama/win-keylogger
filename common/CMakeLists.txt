add_library (
    common
    SHARED

    keyboard/listener.c
    log/logger.c
    memory/memory.c
    memory/shared.c
    tcp/client.c
)
target_link_libraries(common ws2_32)
target_include_directories(common PRIVATE .)