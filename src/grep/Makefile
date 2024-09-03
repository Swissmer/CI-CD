CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -D_GNU_SOURCE

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep || exit 1

test: rebuild
	sh test_func_grep.sh
	sh test_leak_grep.sh
	make clean

check: clean
	cp ../../materials/linters/.clang-format ../../src/grep/.clang-format
	clang-format -Werror -n *.c *.h
	rm .clang-format

clean: 
	rm -rf s21_grep s21_grep.dSYM s21_grep_test.txt grep_test.txt .clang-format

rebuild: clean all