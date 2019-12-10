#ifndef INPUT_BUFFER_H_
# define INPUT_BUFFER_H_

#include <stddef.h>
#include <sys/types.h>

struct input_buffer {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

void print_prompt(void);
struct input_buffer *new_input_buffer(void);
void read_input(struct input_buffer* input_buffer);
void close_input_buffer(struct input_buffer* input_buffer);

#endif
