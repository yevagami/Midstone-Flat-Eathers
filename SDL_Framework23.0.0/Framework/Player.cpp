#include "Player.h"

Player::Player() {
	dash_timer = new Clock(dashDuration, false);
	dash_cooldown = new Clock(dashCooldown, false);
	cooldowns.push_back(dash_cooldown);

	currentSpeed = walkSpeed;
	currentState = idle;
}


void Player::Update(float deltaTime){
	//state machine
	switch (currentState) {
		//Idle state
		case idle: 
			std::cout << "idle state\n";
			break;

		//Walk state
		case walk:
			currentSpeed = walkSpeed;
			std::cout << "walk state\n";
			break;

		//Dash state
		case dash:
			std::cout << "dash state " << "time elapsed: " << dash_timer->timer << "\n";
			dash_timer->Update(deltaTime);
			currentSpeed = dashSpeed;

			if (dash_timer->completed) {
				currentSpeed = walkSpeed;
				dash_timer->Reset();
				dash_cooldown->Start();
				currentState = idle;
			}
			break;
	}

	for (Clock* cd : cooldowns) {
		if (cd->hasStarted) {
			cd->Update(deltaTime);
			if (cd->completed) { cd->Reset(); }
		}
	}

	vel = Vec3(movement.x * currentSpeed, movement.y * currentSpeed, 0.0f);
	Body::Update(deltaTime);

}


void Player::playerController(const SDL_Event& sdlEvent){
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	//resets the input each frame
	movement = Vec2(0.0f, 0.0f);

	//movement controls
	if (keyStates[SDL_SCANCODE_W] == 1) { movement.y += 1.0f;}
	if (keyStates[SDL_SCANCODE_S] == 1) { movement.y -= 1.0f;}
	if (keyStates[SDL_SCANCODE_A] == 1) { movement.x -= 1.0f;}
	if (keyStates[SDL_SCANCODE_D] == 1) { movement.x += 1.0f;}
	if (VMath::mag(movement) > VERY_SMALL) {
		currentState = walk;
	}
	else {
		currentState = idle;
	}


	//dash controls
	if (keyStates[SDL_SCANCODE_LSHIFT] == 1 && currentState != dash && (!dash_cooldown->hasStarted || dash_cooldown->completed)) {
		currentState = dash;
		dash_timer->Start();
	}
}

Player::~Player(){
	for (Clock* item : cooldowns) { delete item; }
	cooldowns.clear();
	delete dash_timer;
}
