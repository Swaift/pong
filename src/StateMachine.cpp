#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "State.hpp"
#include "PlayState.hpp"

StateMachine::StateMachine() {
    this->currentState = new PlayState();
}

StateMachine::~StateMachine() {
    delete currentState;
}

void StateMachine::changeState(State* newState) {
    delete currentState;
    currentState = newState;
}

void StateMachine::execute(sf::RenderWindow& window) {
    currentState->execute(window);
}

void StateMachine::display(sf::RenderWindow& window) {
    currentState->display(window);
}
