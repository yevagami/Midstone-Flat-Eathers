#pragma once
#include <iostream>

class Clock{
public:
	Clock();
	Clock(float duration_);
	void (*callback)();
	void Update(float deltaTime);
	void OnDestroy();
	void Reset();

private:
	float duration;
	float timer = 0;
	bool completed = false;
};

