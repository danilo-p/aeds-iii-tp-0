SHELL:=/bin/bash -O globstar

OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include

SRC=$(wildcard $(SRC_DIR)/*.c)

CFLAGS += -Wall -I$(INC_DIR) -lm

all: setup main run docs

main: main.o
	gcc -Wall -lm -o $(BIN_DIR)/main $(SRC) $(OBJ_DIR)/main.o -I$(INC_DIR)

main.o:
	gcc -Wall -lm -o $(OBJ_DIR)/main.o -c main.c -I$(INC_DIR)

setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

run:
	exec $(BIN_DIR)/main

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

docs:
	doxygen