#include "StateMachine.h"

void StateMachine::changeState(State* nextState){
	if (nextState != currentState) {
		currentState = nextState;
		currentState->enterState();
	}
}
