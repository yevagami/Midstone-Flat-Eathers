#pragma once
#include "Body.h"
#include "Clock.h"
#include <vector>


class Player : public Body{
	//timers and cooldowns
	Clock* dash_timer;
	Clock* dash_cooldown;
	std::vector<Clock*> cooldowns;

	//dashing variables
	float dashDuration = 0.5f;
	float dashCooldown = 0.3f;

	//movement variables
	Vec2 movement;
	float walkSpeed = 200.0f;
	float dashSpeed = 1000.0f;
	float currentSpeed;
	float maxSpeed = 500.0f;

	//states
	enum states{idle, walk, dash};
	states currentState;

public:
	Player();
	void Update(float deltaTime);
	void playerController(const SDL_Event& sdlEvent);
	~Player();
};

