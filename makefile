# makefile for the paddles game
# compiler flags
CPPFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: paddles

paddles: main.o paddles.o
	g++ src/main.o src/paddles.o -o Paddles $(CPPFLAGS)

main.o: src/main.cpp
	gcc -c  src/main.cpp -o src/main.o

paddles.o: src/paddles.cpp src/paddles.hpp
	gcc -c src/paddles.cpp -o src/paddles.o

clean:
	rm src/*.o
	rm bin/*
