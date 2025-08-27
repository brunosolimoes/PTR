# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos fonte (dentro de src)
SRC = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto (serão gerados em obj)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Executável de saída
TARGET = main

# Alvo padrão
all: $(TARGET)

# Linka os arquivos objeto para criar o executável
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

# Compila cada arquivo .c em um arquivo .o dentro de obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos objeto e o executável
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Executa o programa
run: $(TARGET)
	./$(TARGET)

# Alvos "phony"
.PHONY: all clean run