all: game

game: bin/main.o
	g++ bin/main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
bin/main.o: src/main.cpp
	g++ -c -g -Wall -Wextra -std=c++11 src/main.cpp -o bin/main.o

.PHONY: test clean

test: game
	./game

clean:
	rm -f game
	rm -f bin/main.o
