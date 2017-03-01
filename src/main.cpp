#include <iostream>

#define WIDTH 40
#define HEIGHT 20
#define GRASS '~'
#define PLAYER 'p'

void buildMap (char (&map) [HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = GRASS;
        }
    }
}

void printMap (char (&map) [HEIGHT][WIDTH], int playerx, int playery) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == playery && j == playerx) {
                std::cout << PLAYER;
            } else {
                std::cout << map[i][j];
            }
        }
        std::cout << std::endl;
    }
}

int main () {
    char map[HEIGHT][WIDTH];
    int playerx = WIDTH/2;
    int playery = HEIGHT/2;
    buildMap(map);
    printMap(map, playerx, playery);
    while (1) {
        // TODO implement player movement
    }
    return 0;
}
