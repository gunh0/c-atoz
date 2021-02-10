# Makefile for hello.c

# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Target executable
TARGET = hello

# Source files
SRC = hello.c

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
