#include "PlayerBody.h"
#include <SDL_image.h>
#include "Scene.h"
#include "Level.h"
#include "projectile.h"

bool PlayerBody::OnCreate(){
	//Create the melee hitbox
	meleeHitbox = new Hitbox(64, 64, pos.x, pos.y);

    //Creating timers
    dash_timer = new Clock(dashDuration, false);
    dash_cooldown = new Clock(dashCooldown, false);
	shooting_cooldown = new Clock(shootingCooldown, false);
    cooldowns.push_back(dash_cooldown);
	cooldowns.push_back(shooting_cooldown);

    //set the maxSpeed to the currentSpeed
    currentSpeed = walkSpeed;
    maxSpeed = currentSpeed;
    currentState = idle;

    //add a texture to the player
    image = IMG_Load("Textures/programmer_art/player.png");
	SDL_Renderer* renderer = parentScene->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }

	//Failsafe incase the programmer forgets the parentScene
	if (parentScene == nullptr) { 
		std::cout << "You forgot the parentScene for the Player";
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

	//dash controls
	if (keyStates[SDL_SCANCODE_LSHIFT] == 1 && currentState != dash && (!dash_cooldown->hasStarted || dash_cooldown->completed)) {
		currentState = dash;
		dash_timer->Start();
	}

	//melee controls
	if (SDL_MOUSEBUTTONDOWN) {

		if (event.button.button == SDL_BUTTON_LEFT) {
			currentState = melee;
			std::cout << "Pressed left\n";
		}

		if (event.button.button == SDL_BUTTON_RIGHT && currentState != shooting && (!shooting_cooldown->hasStarted || shooting_cooldown->completed)) {
			currentState = shooting;
			std::cout << "Pressed right\n";
		}
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

	case walk:
		currentSpeed = walkSpeed;
		maxSpeed = walkSpeed;
		break;


		//Dash state
	case dash:
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

		//Resets the timer when the duration has elapsed 
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

	case melee:
		currentState = idle;
		break;

	case shooting:
		shooting_cooldown->Start();
		projectile* bullet = new projectile(
			parentLevel,
			pos,
			mouseDirection * projectileSpeed,
			Vec3(0.1f, 0.1f, 0.1f),
			64, 64,
			1.0f
		);
		parentLevel->spawningBodies.push_back(bullet);
		bullet = nullptr;
		currentState = idle;
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


	//Update the melee hitbox
	//Gets the direction of the mouse relative to the player's position
	updateMouseDir();
	updateMeleeHitbox();
}

void PlayerBody::RenderHitbox(SDL_Renderer* renderer_){
	//Render the melee hitbox
	SDL_Rect box;

	box.x = static_cast<int>(meleeHitbox->x);
	box.y = static_cast<int>(meleeHitbox->y);
	box.w = static_cast<int>(meleeHitbox->w);
	box.h = static_cast<int>(meleeHitbox->h);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer_, &box);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

	Body::RenderHitbox(renderer_);
}

void PlayerBody::OnDestroy(){
	for (Clock* item : cooldowns) { delete item; }
	cooldowns.clear();
	dash_timer = nullptr;
	dash_cooldown = nullptr;

	Body::OnDestroy();
}

PlayerBody::~PlayerBody(){
	OnDestroy();
}

void PlayerBody::updateMouseDir(){
	//Gets the direction of the mouse relative to the player's position
	Matrix4 projectionMat = parentScene->getInverseMatrix();
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Vec3 mousePos = projectionMat * Vec3(mouseX, mouseY, 0.0f);

	Vec3 mouseDir = VMath::normalize(Vec3(
		mousePos.x - pos.x,
		mousePos.y - pos.y,
		0.0f
	));
	//std::cout << "(" << mouseDir.x << ", " << mouseDir.y << ")" << "(" << pos.x << ", " << pos.y << ")\n";
	mouseDirection = mouseDir;
}

void PlayerBody::updateMeleeHitbox() {
	Matrix4 projectionMat = parentScene->getProjectionMatrix();
	Vec3 hitboxPos = Vec3(
		pos.x + (mouseDirection.x * (meleeHitbox->w + 100.0f)),
		pos.y + (mouseDirection.y * (meleeHitbox->h + 100.0f)),
		0.0f
	);
	Vec3 hitboxPosScreen = projectionMat * hitboxPos;
	meleeHitbox->x = hitboxPosScreen.x - meleeHitbox->w * 0.5f;
	meleeHitbox->y = hitboxPosScreen.y - meleeHitbox->h * 0.5f;
}