#include "Player.h"
Player::Player() {
	//Creating timers
	dash_timer = new Clock(dashDuration, false);
	dash_cooldown = new Clock(dashCooldown, false);
	cooldowns.push_back(dash_cooldown);

	//set the maxSpeed to the currentSpeed
	currentSpeed = walkSpeed;
	maxSpeed = currentSpeed;
	currentState = idle;
}


void Player::Update(float deltaTime){
	//state machine
	switch (currentState) {
		//Idle state
		case idle: 
			//std::cout << "idle state \n";
			canMove = true;
			break;


		//Walk state
		case walk:
			//std::cout << "walk state \n";
			currentSpeed = walkSpeed;
			maxSpeed = walkSpeed;
			break;


		//Dash state
		case dash:
			//std::cout << "dash state " << "time elapsed: " << dash_timer->timer << "\n";
			canMove = false; //disables the player's movement input
			dash_timer->Update(deltaTime); 

			//set the max speed to the dash speed
			currentSpeed = dashSpeed; 
			maxSpeed = dashSpeed;

			//cap the dash speed so the player doesn't move faster when moving diagonally 
			if (VMath::mag(vel) > maxSpeed) {
				float newSpeed = sqrt((currentSpeed * currentSpeed) / 2);
				vel = Vec3(playerDirection.x * newSpeed, playerDirection.y * newSpeed, 0.0f);
			}
			else { 
				vel = Vec3(playerDirection.x * currentSpeed, playerDirection.y * currentSpeed, 0.0f); 
			}


			if (dash_timer->completed) {
				//set the current and max speed;
				currentSpeed = walkSpeed;
				maxSpeed = walkSpeed;

				//reset the timer and start the cooldown
				dash_timer->Reset();
				dash_cooldown->Start();
				vel = Vec3(); //reset the player's speed and set the state to idle
				currentState = idle;
			}
			break;
	}

	//update the cooldown timers
	for (Clock* cd : cooldowns) {
		if (cd->hasStarted) {
			cd->Update(deltaTime);
			if (cd->completed) { cd->Reset(); }
		}
	}

	//cap the player's movement speed
	if(canMove){ 
		if (VMath::mag(vel) > maxSpeed) {
			float newSpeed = sqrt((currentSpeed * currentSpeed) / 2);
			vel = Vec3(movement.x * newSpeed, movement.y * newSpeed, 0.0f);
		}
		else { 
			vel = Vec3(movement.x * currentSpeed, movement.y * currentSpeed, 0.0f); 
		}
	}

	//update the body 
	Body::Update(deltaTime);
}


void Player::playerController(const SDL_Event& sdlEvent){
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	//resets the input each frame
	movement = Vec2(0.0f, 0.0f);
	
	//movement controls
	if (canMove) {
		if (keyStates[SDL_SCANCODE_W] == 1) { movement.y += 1.0f;}
		if (keyStates[SDL_SCANCODE_S] == 1) { movement.y -= 1.0f;}
		if (keyStates[SDL_SCANCODE_A] == 1) { movement.x -= 1.0f;}
		if (keyStates[SDL_SCANCODE_D] == 1) { movement.x += 1.0f;}

		//if the movement keys are pressed, set the state to walk
		if(VMath::mag(movement) > VERY_SMALL){ 
			currentState = walk;
			playerDirection = movement;
		}
		else { currentState = idle; }
	}

	//	dash controls
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

