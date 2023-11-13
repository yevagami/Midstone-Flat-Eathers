#include "PlayerBody.h"
#include <SDL_image.h>
#include "Scene.h"
#include "Level.h"
#include "Projectile.h"

bool PlayerBody::OnCreate(){
	//Setting the variables
	maxHealth = maxPlayerHealth;
	currentHealth = maxHealth;

	//Create the melee hitbox
	meleeHitbox = new Hitbox(64, 64, pos.x, pos.y);

    //Creating timers
	//Note: these timers will be independent of the clock updating pool 
	//because they need to be activated and updated in certain circumstances
    dash_timer = new Clock(dashDuration, false);
	invincible_timer = new Clock(invincibleDuration, false);

	//These ones will be part of the update pool
    dash_cooldown = new Clock(dashCooldown, false);
	shooting_cooldown = new Clock(shootingCooldown, false);
    cooldowns.push_back(dash_cooldown);
	cooldowns.push_back(shooting_cooldown);

    //set the maxSpeed to the currentSpeed
    currentSpeed = walkSpeed;
    maxSpeed = currentSpeed;
    currentState = idle;

    //add a texture to the player
	playerSprite = Sprite("Textures/programmer_art/sprite_sheet.png", parentScene->getRenderer());
	if (!playerSprite.autoLoadSprites()) {
		std::cerr << "Error with the sprites" << std::endl;
		return false;
	}
	/*
    image = IMG_Load("Textures/programmer_art/player.png");
	SDL_Renderer* renderer = parentScene->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
	*/

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
	if (keyStates[SDL_SCANCODE_SPACE] == 1 && currentState != dash && (!dash_cooldown->hasStarted || dash_cooldown->completed)) {
		currentState = dash;
		dash_timer->Start();
	}

	//melee controls
	if (SDL_MOUSEBUTTONUP) {

		if (event.button.button == SDL_BUTTON_LEFT) {
			currentState = melee;
			//std::cout << "Pressed left\n";
		}

		if (event.button.button == SDL_BUTTON_RIGHT && currentState != shooting && (!shooting_cooldown->hasStarted || shooting_cooldown->completed)) {
			currentState = shooting;
			//std::cout << "Pressed right\n";
		}
	}
}

void PlayerBody::Update( float deltaTime ){
	//If the destroy flag has been set, the player is now dead
	if (currentHealth <= 0) { std::cout << "YOU DIED LMAO \n"; }

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
			//vel = Vec3(); //reset the player's speed and set the state to idle
			currentState = idle;
			canMove = true;
		}
		break;

	case melee:

		for (Body* other : parentLevel->levelBodies) {
			if (other->type == PLAYER) { continue; }
			if (other->getHitbox()->collisionCheck(meleeHitbox)) {
				if (other->type == SOLID) { std::cout << "You hit a solid\n"; }
				if (other->type == ENEMY) {
					std::cout << "You hit an enemy\n"; 
					other->takeDamage(meleePower);
				}
			}
		}
		currentState = idle;
		break;

	case shooting:
		shooting_cooldown->Start();
		Projectile* bullet = new Projectile(
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
		cd->Update(deltaTime);
		if (cd->completed) { cd->Reset(); }
	}

	if (invincible) {
		invincible_timer->Update(deltaTime);
		if (invincible_timer->completed) { 
			invincible = false; 
			invincible_timer->Reset();
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

void PlayerBody::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){
	SDL_Rect square;
	Vec3 screenCoords;
	float w, h;

	// convert the position from game coords to screen coords.
	screenCoords = projectionMatrix_ * pos;

	// Scale the image, in case the .png file is too big or small
	w = 128.0f * scale.x;
	h = 128.0f * scale.y;

	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);

	// Convert character orientation from radians to degrees.
	float orientationDegrees = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer_, playerSprite.spriteSheet, &playerSprite.spriteStorage[1], &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);
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

	delete dash_timer;
	delete invincible_timer;

	playerSprite.onDestroy();

	Body::OnDestroy();
}

PlayerBody::~PlayerBody(){
	OnDestroy();
}

void PlayerBody::updateMouseDir(){
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
	//std::cout << "(" << mousePos.x << ", " << mousePos.y << ")" << "(" << pos.x << ", " << pos.y << ")\n";
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

void PlayerBody::takeDamage(float amount){
	if (invincible) { return; }
	currentHealth -= amount - ((amount * (playerDefense / 100)) * 0.8);
	std::cout << "Player took damage\n";
	invincible_timer->Start();
	invincible = true;
}
