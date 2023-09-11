#pragma once
#include "Body.h"

class Player : public Body{
	Vec2 movement;

	float walkSpeed = 200.0f;
	float currentSpeed;
	float maxSpeed = 200.0f;

public:
	Player();
	void Update(float deltaTime);
	void playerController(const SDL_Event& sdlEvent);
};

