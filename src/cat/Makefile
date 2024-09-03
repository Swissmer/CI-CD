CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -D_GNU_SOURCE

all: s21_cat
	
s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat || exit 1

test: clean all
	sh test_func_cat.sh
	sh test_leak_cat.sh
	make clean

check: clean
	cp ../../materials/linters/.clang-format ../../src/cat/.clang-format
	clang-format -Werror -n *.c *.h
	rm .clang-format

clean:
	rm -rf s21_cat s21_cat.dSYM s21_cat_test.txt cat_test.txt .clang-format

rebuild: clean all