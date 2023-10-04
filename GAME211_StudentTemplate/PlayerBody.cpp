//
//  PlayerBody.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "PlayerBody.h"

bool PlayerBody::OnCreate()
{
    //Creating timers
    dash_timer = new Clock(dashDuration, false);
    dash_cooldown = new Clock(dashCooldown, false);
    cooldowns.push_back(dash_cooldown);

    //set the maxSpeed to the currentSpeed
    currentSpeed = walkSpeed;
    maxSpeed = currentSpeed;
    currentState = idle;

    //add a texture to the player
    image = IMG_Load( "Textures/Pacman.png" );
    SDL_Renderer *renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    return true;
}

void PlayerBody::HandleEvents( const SDL_Event& event ){
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	//resets the input each frame
	movement = Vec3();

	//movement controls
	if (canMove) {
		if (keyStates[SDL_SCANCODE_W] == 1) { movement.y += 1.0f; }
		if (keyStates[SDL_SCANCODE_S] == 1) { movement.y -= 1.0f; }
		if (keyStates[SDL_SCANCODE_A] == 1) { movement.x -= 1.0f; }
		if (keyStates[SDL_SCANCODE_D] == 1) { movement.x += 1.0f; }

		//if the movement keys are pressed, set the state to walk
		if (VMath::mag(movement) > VERY_SMALL) {
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

void PlayerBody::Update( float deltaTime ){
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
	if (canMove) {
		if (VMath::mag(vel) > maxSpeed) {
			float newSpeed = sqrt((currentSpeed * currentSpeed) / 2);
			vel = Vec3(movement.x * newSpeed, movement.y * newSpeed, 0.0f);
		}
		else {
			vel = Vec3(movement.x * currentSpeed, movement.y * currentSpeed, 0.0f);
		}
	}


    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion
    Body::Update( deltaTime );

}

void PlayerBody::CollisionResponse(float deltaTime, Body* other){
	pos.x -= vel.x * deltaTime;
	pos.y -= vel.y * deltaTime;
	pos.z -= vel.z * deltaTime;
}

PlayerBody::~PlayerBody(){
    for (Clock* item : cooldowns) { delete item; }
    cooldowns.clear();
}

