# 0 - последовательное умножение матрицы
# 1 - обычное умножение матрицы openmp
# 2 - необычное умножение матрицы openmp
TYPE_MUL = -DMATRTIX_MUL=2

TARGET = main

COMPILER = g++
FLAGS = -std=c++0x -O2 -Wall -Wextra -Wpedantic -fopenmp

OS := $(shell uname)
ifeq ($(OS),Darwin)
	COMPILER = g++-7
endif

ifdef SYSTEMROOT
    RM = del /Q
else
    RM = rm -f
endif


default: $(TARGET)

$(TARGET): main.o Matrix.o functions.o
	$(COMPILER) $(FLAGS) main.o Matrix.o functions.o -o $@

main.o: main.cpp
	$(COMPILER) -c $(FLAGS) main.cpp

functions.o: functions.cpp
	$(COMPILER) -c $(FLAGS) functions.cpp

Matrix.o: Matrix.cpp
	$(COMPILER) -c $(FLAGS) $(TYPE_MUL) Matrix.cpp

clean:
	$(RM) *.o

clean_all:
	$(RM) *.o main