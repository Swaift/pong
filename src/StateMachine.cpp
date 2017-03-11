#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "State.hpp"
#include "SplashState.hpp"

StateMachine::StateMachine() {
    this->currentState = new SplashState();
}

StateMachine::~StateMachine() {
    delete currentState;
}

void StateMachine::execute(sf::RenderWindow& window) {
    currentState->execute(window);
}

void StateMachine::draw(sf::RenderWindow& window) {
    currentState->draw(window);
}

void StateMachine::changeState() {
    if (currentState->getNextState() != currentState) {
        State* nextState = currentState->getNextState();
        delete currentState;
        currentState = nextState;
    }
}
