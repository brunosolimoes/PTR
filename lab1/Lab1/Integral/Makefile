all: main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@" -lm

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@" -lm

clean:
	rm -f main main-debug

# Regra para executar o programa
run: main
	./main

# Regra para executar a versão de depuração
run-debug: main-debug
	./main-debug
