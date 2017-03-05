all: game

game: bin/main.o bin/states.o
	g++ bin/main.o bin/states.o -o game -lsfml-graphics -lsfml-window -lsfml-system
bin/main.o: src/main.cpp inc/states.h
	g++ src/main.cpp -o bin/main.o -c -g -Wall -Wextra -std=c++11 -Iinc
bin/states.o: src/states.cpp inc/states.h
	g++ src/states.cpp -o bin/states.o -c -g -Wall -Wextra -std=c++11 -Iinc

.PHONY: test clean

test: game
	./game

clean:
	rm -f game
	rm -f bin/*
