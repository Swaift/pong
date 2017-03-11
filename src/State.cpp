#include "State.hpp"

State::State() {
    nextState = this;
}

State* State::getNextState() {
    return nextState;
}

void State::setNextState(State* nextState) {
    this->nextState = nextState;
}
