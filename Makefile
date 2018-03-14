COMPILER = g++

FLAGS = -std=c++0x -O2 -Wall -Wextra -Wpedantic -fopenmp
#FLAGS = -std=c++11

OS := $(shell uname)
ifeq ($(OS),Darwin)
	COMPILER = g++-7
endif

ifdef SYSTEMROOT
    RM = del /Q
else
    RM = rm -f
endif


default: all

all: clean main.o Matrix.o functions.o
	$(COMPILER) $(FLAGS) main.o Matrix.o functions.o -o main

main.o: 
	$(COMPILER) -c $(FLAGS) main.cpp -o main.o

functions.o: 
	$(COMPILER) -c $(FLAGS) functions.cpp -o functions.o

Matrix.o:
	$(COMPILER) -c $(FLAGS) Matrix.cpp -o Matrix.o

clean:
	$(RM) *.o all
