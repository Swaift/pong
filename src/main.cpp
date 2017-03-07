#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "play.hpp"
#include <cstdlib>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");

    // initialize state machine
    enum class State {
        SPLASH,
        PLAY,
        GAMEOVER
    };
    State currentState = State::PLAY;
    State nextState = State::PLAY;

    play::initializePlay();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        currentState = nextState;
        switch (currentState) {
            case State::SPLASH:
                // TODO
                nextState = State::SPLASH;
                break;
            case State::PLAY:
                play::executePlay(window);
                nextState = State::PLAY;
                break;
            case State::GAMEOVER:
                // TODO
                nextState = State::GAMEOVER;
                break;
        }

        window.display();
    }

    return 0;
}
