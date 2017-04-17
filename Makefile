SHELL:=/bin/bash -O globstar

OBJ_DIR=obj/
BIN_DIR=bin/
HEADER_DIR=headers/

all: setup main run docs

main: main.o
	gcc -Wall -o $(BIN_DIR)main $(HEADER_DIR)**/*.c $(OBJ_DIR)main.o

main.o:
	gcc -Wall -o $(OBJ_DIR)main.o -c main.c

setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

run:
	exec $(BIN_DIR)main

clean:
	rm -f $(OBJ_DIR)* $(BIN_DIR)*

docs:
	doxygen