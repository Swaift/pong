#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "StateMachine.hpp"
#include <cstdlib>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");
    StateMachine machine;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        machine.execute(window);
        window.display();
    }

    return 0;
}
