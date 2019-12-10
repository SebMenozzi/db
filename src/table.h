#ifndef TABLE_H_
# define TABLE_H_

#include <stdint.h>
#include "row.h"

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_PAGES = 100;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

struct table
{
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
};

struct table *new_table(void);
void free_table(struct table *table);
void* row_slot(struct table *table, uint32_t row_num);

#endif
