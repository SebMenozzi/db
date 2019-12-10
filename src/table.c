#include "table.h"
#include <stdlib.h>

struct table *new_table(void)
{
    struct table *table = malloc(sizeof(struct table));
    table->num_rows = 0;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; ++i)
        table->pages[i] = NULL;

    return table;
}

void free_table(struct table *table)
{
    for (int i = 0; table->pages[i]; i++)
        free(table->pages[i]);

    free(table);
}

void* row_slot(struct table *table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];

    if (page == NULL)
    {
        // Allocate memory only when we try to access page
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
