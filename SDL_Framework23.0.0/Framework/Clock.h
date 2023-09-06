#pragma once
#include <iostream>

class Clock{
	float duration;
	float timer = 0
	unsigned int (*function) ();

	void Update(float deltaTime);
	void CallBack(callback);
	void OnDestroy();
};

