CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 #-fsanitize-memory-track-origins #-fsanitize=address -fno-omit-frame-pointer -g
CHECK_FLAGS = $(shell pkg-config --libs check)
GCOV_FLAGS = --coverage

# Список исходных файлов
LIB_SRC_FILES = s21_matrix.c
# Список объектных файлов
LIB_OBJ_FILES = s21_matrix.o
TEST_C = tests.c

.PHONY: all clean test s21_matrix.a gcov_report

all: clean s21_matrix.a

$(LIB_OBJ_FILES): $(LIB_SRC_FILES)
	$(CC) $(CFLAGS) -c $^

s21_matrix.a: $(LIB_OBJ_FILES)
	ar rcs $@ $^

test: s21_matrix.a $(TEST_C)
	$(CC) $(CFLAGS) $(TEST_C) -o $@ $(CHECK_FLAGS) -L. s21_matrix.a -lm

gcov_report:  $(TEST_C) $(LIB_SRC_FILES)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c s21_matrix.c -o s21_matrix_gcov.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_C) s21_matrix_gcov.o -o $@ $(CHECK_FLAGS) -lm
	./gcov_report
	gcov -a $(TEST_C)
	gcov -a s21_matrix_gcov.o
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	open coverage_html/index.html

clean:
	rm -f $(LIBRARY) $(LIB_OBJ_FILES) test *.out *.gch *.gcov *.gcda *.gcno *.o *.a coverage.info gcov_report test
	clang-format -i *.c *.h --style=Google