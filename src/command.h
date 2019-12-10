#ifndef COMMAND_H_
# define COMMAND_H_

#include "input_buffer.h"
#include "row.h"
#include "table.h"
#include <stdint.h>

enum prepare_result
{
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum statement_type
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
};

struct statement
{
    enum statement_type type;
    struct row row_to_insert;
};

enum execute_result
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
};

enum prepare_result prepare_statement(struct input_buffer *input_buffer, struct statement *statement);
enum execute_result execute_statement(struct statement *statement, struct table *table);

#endif
