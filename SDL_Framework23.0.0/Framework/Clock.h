#pragma once
#include <iostream>

class Clock{
public:
	Clock();
	Clock(float duration_, bool isLooping_);
	void (*callback)();
	void Update(float deltaTime);
	void OnDestroy();
	void Reset();

private:
	float duration;
	float timer = 0;
	bool completed = false;
	bool isLooping = false;
};

