#pragma once
#include "Body.h"
#include "Clock.h"
#include <vector>


class Player : public Body{
	//timers and cooldowns
	Clock* dash_timer; //how long the player can dash for
	Clock* dash_cooldown; //how long before the player can dash again
	std::vector<Clock*> cooldowns; //list of cooldowns to update

	//dashing variables
	float dashDuration = 0.5f;
	float dashCooldown = 0.3f;

	//movement variables
	Vec2 movement;
	Vec2 playerDirection;
	bool canMove = true;
	float walkSpeed = 500.0f;
	float dashSpeed = 2000.0f;
	float currentSpeed;
	float maxSpeed;

	//states
	enum states{idle, walk, dash};
	states currentState;

public:
	Player();
	void Update(float deltaTime);
	void playerController(const SDL_Event& sdlEvent);
	~Player();
};

