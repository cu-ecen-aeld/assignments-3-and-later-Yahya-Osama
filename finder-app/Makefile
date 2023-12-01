
# Author      : Yahya Osama Mohamed
# Date        : 26 Sept 2023
# Description : Assignment 2


# Define the compiler
CC = $(CROSS_COMPILE)gcc

# Define the source and object files
SRC = writer.c
OBJ = writer

# Default target to build the writer application
default: $(OBJ)

# Target to build the writer application
$(OBJ): $(SRC)
	$(CC) -o $@ $^

# Clean target to remove the writer application and .o files
clean:
	rm -f $(OBJ)

.PHONY: default clean
