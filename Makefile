SHELL:=/bin/bash -O globstar

ROOT_DIR=$(pwd)
OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
DOCS_DIR=docs

SRC=$(wildcard $(SRC_DIR)/**/*.c)

CFLAGS += -lm -Wall -Wextra -Werror -std=c99 -pedantic -O2

.PHONY: all docs

all: setup main

main: main.o
	gcc $(SRC) $(OBJ_DIR)/matriz.o -o $(BIN_DIR)/matriz $(CFLAGS)
	gcc $(SRC) $(OBJ_DIR)/arvore.o -o $(BIN_DIR)/arvore $(CFLAGS)

main.o:
	gcc -c $(SRC_DIR)/matriz.c -o $(OBJ_DIR)/matriz.o $(CFLAGS)
	gcc -c $(SRC_DIR)/arvore.c -o $(OBJ_DIR)/arvore.o $(CFLAGS)

setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

run:
	exec $(BIN_DIR)/${TARGET}

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

docs:
	doxygen && cd $(DOCS_DIR)/latex && make

valgrind:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(BIN_DIR)/${TARGET}
