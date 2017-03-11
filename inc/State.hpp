#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State {
    public:
        State();
        virtual ~State() {}
        virtual void execute(sf::RenderWindow& window) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        State* getNextState();
        void setNextState(State* nextState);
    private:
        State* nextState;
};

#endif // STATE_HPP
