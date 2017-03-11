#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"

class SplashState: public State {
    public:
        SplashState();
        void execute(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
    private:
        sf::Font font;
        sf::Text titleText;
        sf::Text playText;
};

#endif // SPLASHSTATE_HPP
