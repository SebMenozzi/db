#include "command.h"
#include "input_buffer.h"
#include "table.h"
#include "row.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum prepare_result prepare_insert(struct input_buffer *input_buffer, struct statement *statement)
{
    statement->type = STATEMENT_INSERT;

    char *keyword = strtok(input_buffer->buffer, " ");
    char *id_string = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL)
        return PREPARE_SYNTAX_ERROR;

    if (strlen(username) > COLUMN_USERNAME_SIZE)
        return PREPARE_STRING_TOO_LONG;

    if (strlen(email) > COLUMN_EMAIL_SIZE)
        return PREPARE_STRING_TOO_LONG;

    int id = atoi(id_string);

    if (id < 0)
        return PREPARE_NEGATIVE_ID;

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

enum prepare_result prepare_statement(struct input_buffer *input_buffer, struct statement *statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
        return prepare_insert(input_buffer, statement);

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

    serialize_row(row_to_insert, get_row(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

enum execute_result execute_select(struct statement *statement, struct table *table)
{
    struct row row;

    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(get_row(table, i), &row);
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
