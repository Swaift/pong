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
