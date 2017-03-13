#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"

class GameOverState: public State {
    public:
        GameOverState(bool win);
        void execute(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
    private:
        sf::Font font;
        sf::Text gameResultText;
        sf::Text playAgainText;
        sf::SoundBuffer pointBuffer;
        sf::Sound pointSound;
        bool firstFrame;
};

#endif // GAMEOVERSTATE_HPP
