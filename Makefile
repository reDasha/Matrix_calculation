CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 #-fsanitize-memory-track-origins #-fsanitize=address -fno-omit-frame-pointer -g
CHECK_FLAGS = $(shell pkg-config --libs check)
GCOV_FLAGS = --coverage

# Список исходных файлов
LIB_SRC_FILES = s21_matrix.c
# Список объектных файлов
LIB_OBJ_FILES = s21_matrix.o

.PHONY: all clean s21_matrix.a

all: clean s21_matrix.a

$(LIB_OBJ_FILES): $(LIB_SRC_FILES)
	$(CC) $(CFLAGS) -c $^

s21_matrix.a: $(LIB_OBJ_FILES)
	ar rcs $@ $^

install:
	make clean
	mkdir build
	cd build/ && qmake ../Matrix_QT.pro && make
	open build/Matrix_QT.app

uninstall:
	-rm -rf build*

clean:
	rm -f $(LIBRARY) $(LIB_OBJ_FILES) *.out *.gch *.gcov *.gcda *.gcno *.o *.a
	clang-format -i *.c *.h --style=Google
