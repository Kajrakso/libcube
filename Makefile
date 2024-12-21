# Compiler and standard flags
CC = cc
CFLAGS_COMMON = -std=c99 -pthread -pedantic -Wall -Wextra -Wconversion -Wno-unused-parameter
CFLAGS_OPTIMIZED = -O3
CFLAGS_DEBUG = -g3 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fstack-protector-all -Wno-unused-function

# Targets
LIB = libcube.a
TEST_EXEC = test.out

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Default target
all: CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_OPTIMIZED)
all: $(LIB)

# Debug target
debug: CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
debug: $(LIB)

# Test target
test: CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
test: $(TEST_EXEC)

# Library creation
$(LIB): $(OBJ)
	ar rcs $@ $^

# Test executable
$(TEST_EXEC): $(TEST_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $^ -lcriterion -o $@ && ./$(TEST_EXEC) --verbose=1

# Compile source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(LIB) $(TEST_OBJ) $(TEST_EXEC)

# Phony targets
.PHONY: all debug test clean