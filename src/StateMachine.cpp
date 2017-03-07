#include "StateMachine.hpp"
#include "State.hpp"

StateMachine::StateMachine(State* currentState) {
    this->currentState = currentState;
}

StateMachine::~StateMachine() {
    delete currentState;
}

void StateMachine::changeState(State* newState) {
    delete currentState;
    currentState = newState;
}

void StateMachine::executeCurrentState() {
    currentState->execute();
}
