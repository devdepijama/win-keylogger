add_executable (memreader main.c)
target_include_directories(memreader PUBLIC . ../common)
target_link_libraries (memreader PUBLIC common)