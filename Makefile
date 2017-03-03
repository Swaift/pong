all: rpg

rpg: bin/main.o
	g++ bin/main.o -o rpg -lsfml-graphics -lsfml-window -lsfml-system
bin/main.o: src/main.cpp
	g++ -c -g -Wall -Wextra -std=c++11 src/main.cpp -o bin/main.o

.PHONY: test clean

test: rpg
	./rpg

clean:
	rm rpg
	rm bin/main.o
