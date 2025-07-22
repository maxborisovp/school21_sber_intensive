CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
.PHONY: all strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests clean rebuild

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_processor

strlen_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRLEN_TESTS s21_string.c s21_string_test.c -o ../build/Quest_1

strcmp_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRCMP_TESTS s21_string.c s21_string_test.c -o ../build/Quest_2

strcpy_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRCPY_TESTS s21_string.c s21_string_test.c -o ../build/Quest_3

strcat_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRCAT_TESTS s21_string.c s21_string_test.c -o ../build/Quest_4

strchr_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRCHR_TESTS s21_string.c s21_string_test.c -o ../build/Quest_5

strstr_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRSTR_TESTS s21_string.c s21_string_test.c -o ../build/Quest_6

strtok_tests: s21_string_test.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) -D STRTOK_TESTS s21_string.c s21_string_test.c -o ../build/Quest_7

text_processor: text_processor.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) s21_string.c text_processor.c -o ../build/Quest_8

clean:
	rm -rf ../build/Quest_*

rebuild: clean all
