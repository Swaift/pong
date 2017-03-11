#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State {
    public:
        virtual ~State() {}
        virtual void execute(sf::RenderWindow& window) = 0;
        virtual void display(sf::RenderWindow& window) = 0;
};

#endif // STATE_HPP
