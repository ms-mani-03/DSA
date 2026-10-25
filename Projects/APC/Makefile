CC = gcc
CFLAGS = -Wall -Wextra
TARGET = apc
SRC = main.c apc.c add.c sub.c mul.c div.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean


