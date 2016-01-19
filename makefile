# makefile for the paddles game
# compiler flags
CFLAGS=-c
CPPFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: paddles

paddles: main.o
	g++ bin/main.o -o bin/test $(CPPFLAGS)

main.o: src/main.cpp
	gcc $(CFLAGS) src/main.cpp -o bin/main.o

clean:
	rm bin/*
