#pragma once
#include "Body.h"

class Player : public Body{
	Vec2 movement;

	float walkSpeed = 100.0f;
	float currentSpeed;
	float maxSpeed = 100.0f;

public:
	Player();
	void Update(float deltaTime);
	void playerController(const SDL_Event& sdlEvent);
};

