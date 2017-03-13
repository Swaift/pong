#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "StateMachine.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");
    window.setFramerateLimit(60);
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
        machine.draw(window);
        machine.changeState();
        window.display();
    }

    return 0;
}
