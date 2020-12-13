add_executable (memwriter main.c)
target_include_directories(memwriter PUBLIC . ../common)
target_link_libraries (memwriter PUBLIC common)