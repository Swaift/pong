#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "State.hpp"

class StateMachine {
    public:
        StateMachine(State* currentState);
        ~StateMachine();
        void changeState(State* newState);
        void executeCurrentState();
    private:
        StateMachine(const StateMachine&);
        StateMachine& operator=(const StateMachine&);
        State* currentState;
};

#endif // STATEMACHINE_HPP
