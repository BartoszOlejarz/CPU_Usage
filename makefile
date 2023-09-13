#envirement variable
CC = gcc

#compilation flags
CFLAGS =
ifeq ($(CC),gcc)
	CFLAGS = $(GCC_FLAGS)
else
	CFLAGS = $(CLANG_FLAGS)
endif

GCC_FLAGS = -std=c99 -lm -Wall -Wextra -lpthread
CLANG_FLAGS = -std=c99 -lm -Weverything -lpthread

#rooster
rooster: main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c functions_source/logger.c
	@echo "Compilating final application"
	@$(CC) main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c functions_source/logger.c $(CFLAGS) -o rooster

#subrooster
subrooster: main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c
	@echo "Compilating subfinal application"
	@$(CC) main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c $(CFLAGS) -o subrooster

#simple
simple: main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c
	@echo "Compilating simple application"
	@$(CC) main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c -std=c99 -lpthread -o simple

#debug
debug: main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c
	@echo "Compilating debug application"
	@$(CC) main.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c -g -lpthread -o simple

#test
test: test.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c
	@echo "Compilating test"
	@$(CC) test.c functions_source/analyzer.c functions_source/printer.c functions_source/reader.c functions_source/watchdog.c -lpthread -o test

#clean
clean:
	@echo "Cleaning"
	rm -f rooster subrooster debug simple test
