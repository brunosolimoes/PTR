# Nome do compilador
CC=gcc

# Opções de compilação
CFLAGS=-Wall -g

# Nome do programa final
TARGET=build/simulacao

# Diretório para os arquivos-objeto
BUILD_DIR=build

# Arquivos-objeto
OBJS=$(BUILD_DIR)/main.o $(BUILD_DIR)/model.o $(BUILD_DIR)/estate.o 

# Regra padrão
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Como construir o programa final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Como construir cada objeto individualmente
$(BUILD_DIR)/main.o: main.c model.h estate.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/model.o: model.c model.h
	$(CC) $(CFLAGS) -c model.c -o $(BUILD_DIR)/model.o

$(BUILD_DIR)/estate.o: estate.c estate.h model.h
	$(CC) $(CFLAGS) -c estate.c -o $(BUILD_DIR)/estate.o

# Como limpar os arquivos-objeto e o executável
clean:
	rm -rf $(BUILD_DIR)
