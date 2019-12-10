.PHONY: all clean

CC ?= gcc
CGFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
SRC = src/main.c src/input_buffer.c src/command.c src/row.c src/table.c
OBJS = $(SRC:.c=.o)
BIN = db

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	$(RM) $(OBJS) $(BIN)
