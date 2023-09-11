#envirement variable
CC = gcc

#compilation flags
CFLAGS =
ifeq ($(CC),gcc)
	CFLAGS = $(GCC_FLAGS)
else
	CFLAGS = $(CLANG_FLAGS)
endif

GCC_FLAGS = -std=c99 -lm -Wall -Wextra
CLANG_FLAGS = -std=c99 -lm -Weverything

#all
all: main.c
	@echo "Compilating application"
	@$(CC) main.c $(CFLAGS) -o main

#cleaning
clean:
	@echo "Cleaning"
	rm -f main
