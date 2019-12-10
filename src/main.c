#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_buffer.h"
#include "command.h"
#include "table.h"

int main(int argc, char **argv)
{
    struct table *table = new_table();

    struct input_buffer* input_buffer = new_input_buffer();

    while (1)
    {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0)
            exit(EXIT_SUCCESS);

        struct statement statement;
        enum prepare_result result = prepare_statement(input_buffer, &statement);

        if (result == PREPARE_UNRECOGNIZED_STATEMENT)
        {
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
            continue;
        }
        else if (result == PREPARE_SYNTAX_ERROR)
        {
            printf("Syntax error. Could not parse statement.\n");
            continue;
        }
        else
        {
            enum execute_result result = execute_statement(&statement, table);

            if (result == EXECUTE_TABLE_FULL)
                printf("Error: Table full.\n");
        }
    }
}