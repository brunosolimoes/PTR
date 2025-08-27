CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
LIBS = -lm

SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXEC = my_program

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./$(EXEC)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)