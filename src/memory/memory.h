#ifndef H_MEMORY
#define H_MEMORY

typedef struct {
    char *logName;
    int log_level;
} memory_parameters_s;

void memory_init(memory_parameters_s *parameters);
void * memory_alloc(unsigned int size, char *description);
void memory_free(void *ptr);

#endif