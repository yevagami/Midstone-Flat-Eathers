#pragma once
#include <iostream>

class Clock{
public:
	//Methods
	Clock();
	Clock(float duration_, bool isLooping_);
	void Update(float deltaTime);
	void OnDestroy();
	void Reset();
	void Start();

	//Variables
	bool hasStarted = false;
	float duration;
	float timer = 0;
	bool completed = false;
	bool isLooping = false;
};

