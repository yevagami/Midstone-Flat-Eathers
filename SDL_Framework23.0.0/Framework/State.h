#pragma once

class State{
public:
	virtual void enterState();
	virtual void updateState();
	virtual void exitState();
};

