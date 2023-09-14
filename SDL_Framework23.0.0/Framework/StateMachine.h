#pragma once
#include "State.h"

class StateMachine{
public:
	State* currentState;
	void changeState(State* nextState);
};

