#ifndef TABLE_H_
# define TABLE_H_

#include <stdint.h>
#include "row.h"

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_PAGES = 100;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

struct pager {
    int fd;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
};

struct table
{
    struct pager* pager;
    uint32_t num_rows;
};

struct table *db_open(const char* filename);
struct pager *pager_open(const char *filename);
void db_close(struct table *table);
void pager_flush(struct pager *pager, uint32_t page_num, uint32_t size);
void* get_page(struct pager *pager, uint32_t page_num);
void* get_row(struct table *table, uint32_t row_num);

#endif
