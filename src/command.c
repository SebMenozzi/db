#include "command.h"
#include "input_buffer.h"
#include "table.h"
#include "row.h"
#include <string.h>
#include <stdio.h>

enum prepare_result prepare_statement(struct input_buffer *input_buffer, struct statement *statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;

        int args_assigned = sscanf(
            input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
            statement->row_to_insert.username, statement->row_to_insert.email
        );

        if (args_assigned < 3)
            return PREPARE_SYNTAX_ERROR;

        return PREPARE_SUCCESS;
    }

    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

enum execute_result execute_insert(struct statement *statement, struct table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
        return EXECUTE_TABLE_FULL;

    struct row *row_to_insert = &(statement->row_to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

enum execute_result execute_select(struct statement *statement, struct table *table)
{
    struct row row;

    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }

    return EXECUTE_SUCCESS;
}

enum execute_result execute_statement(struct statement *statement, struct table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
        return EXECUTE_TABLE_FULL;

    if (statement->type == STATEMENT_INSERT)
        return execute_insert(statement, table);

    if (statement->type == STATEMENT_SELECT)
        return execute_select(statement, table);

    return EXECUTE_SUCCESS;
}
