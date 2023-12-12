#pragma once
#include <iostream>
#include <functional>

#ifndef CLOCK_H
#define CLOCK_H

class Clock{
public:
	//Methods
	Clock(float duration_, bool isLooping_);
	Clock(float duration_, bool isLooping_, std::function<void()> callback_);
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
	std::function<void()> callback;
};
#endif // !CLOCK_H
