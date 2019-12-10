#ifndef ROW_H_
# define ROW_H_

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

struct row
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
};

#define size_of_attribute(struct, attribute) sizeof(((struct*)0)->attribute)

static const uint32_t ID_SIZE = size_of_attribute(struct row, id);
static const uint32_t USERNAME_SIZE  = size_of_attribute(struct row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(struct row, email);
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;

void print_row(struct row *row);
void serialize_row(struct row *source, void *destination);
void deserialize_row(void *source, struct row *destination);

#endif
