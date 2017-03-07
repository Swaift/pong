#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "State.hpp"

class StateMachine {
    public:
        StateMachine();
        ~StateMachine();

        void changeState(State* newState);
        template<typename T>
        void execute(T& input) {
            currentState->execute(input);
        }
    private:
        StateMachine(const StateMachine&) = delete;
        StateMachine& operator=(const StateMachine&) = delete;

        State* currentState;
};

#endif // STATEMACHINE_HPP
