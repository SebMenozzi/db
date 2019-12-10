#include "input_buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_prompt(void)
{
    printf("db > ");
}

struct input_buffer *new_input_buffer(void)
{
    struct input_buffer *input_buffer = calloc(1, sizeof(struct input_buffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void read_input(struct input_buffer* input_buffer)
{
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(struct input_buffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}
