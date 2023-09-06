#include "Player.h"

Player::Player() {
	currentSpeed = walkSpeed;
}


void Player::playerController(const SDL_Event& sdlEvent){
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
	movement.set(0.0f, 0.0f);

	if (keyStates[SDL_SCANCODE_W] == 1) { movement.y += 1.0f; }
	if (keyStates[SDL_SCANCODE_S] == 1) { movement.y -= 1.0f; }
	if (keyStates[SDL_SCANCODE_A] == 1) { movement.x -= 1.0f; }
	if (keyStates[SDL_SCANCODE_D] == 1) { movement.x += 1.0f; }

	if (VMath::mag(
		Vec3(movement.x * currentSpeed, movement.y * currentSpeed, 0.0f)) > maxSpeed) {

		currentSpeed = sqrt((currentSpeed * currentSpeed) / 2);
	}
	else {
		currentSpeed = walkSpeed;
	}

	vel = Vec3(movement.x * currentSpeed, movement.y * currentSpeed, 0.0f);
}
