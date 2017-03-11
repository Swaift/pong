#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"

class StateMachine {
    public:
        StateMachine();
        ~StateMachine();

        void changeState(State* newState);
        void execute(sf::RenderWindow& window);
        void display(sf::RenderWindow& window);
    private:
        StateMachine(const StateMachine&) = delete;
        StateMachine& operator=(const StateMachine&) = delete;

        State* currentState;
};

#endif // STATEMACHINE_HPP
