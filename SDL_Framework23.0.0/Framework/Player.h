#pragma once
#include "Body.h"

class Player : public Body{
	Vec2 movement;

	float walkSpeed = 4.0f;
	float currentSpeed;
	float maxSpeed = 4.0f;

public:
	Player();
	void playerController(const SDL_Event& sdlEvent);
};

