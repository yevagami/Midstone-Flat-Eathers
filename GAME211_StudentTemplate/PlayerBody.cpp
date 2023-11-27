#include "PlayerBody.h"
#include "Scene.h"
#include "Level.h"
#include "Projectile.h"
#include "math.h"

bool PlayerBody::OnCreate() {
	//Setting the variables
	maxHealth = playerHealth;
	currentHealth = maxHealth;

	//Create the melee hitbox
	meleeHitbox = new Hitbox(64, 64, pos.x, pos.y);

	//Creating timers
	//Note: these timers will be independent of the clock updating pool 
	//because they need to be activated and updated in certain circumstances
	dash_timer = new Clock(dashDuration, false);
	invincible_timer = new Clock(invincibleDuration, false);
	drawMelee_timer = new Clock(drawMeleeDuration, false); drawMelee_timer = new Clock(drawMeleeDuration, false);

	//These ones will be part of the update pool
	dash_cooldown = new Clock(dashCooldown, false);
	shooting_cooldown = new Clock(shootingCooldown, false);
	cooldowns.push_back(dash_cooldown);
	cooldowns.push_back(shooting_cooldown);

	//set the maxSpeed to the currentSpeed
	currentSpeed = walkSpeed;
	maxSpeed = currentSpeed;
	currentState = idle;

	//Load the sprite sheet
	playerSpriteSheet = Sprite("Textures/programmer_art/sprite_sheet.png", parentScene->getRenderer());
	if (!playerSpriteSheet.autoLoadSprites()) {
		std::cout << "Error in the sprite sheet\n";
		return false;
	}
	image = playerSpriteSheet.image;
	texture = playerSpriteSheet.texture;
	cutout = &playerSpriteSheet.spriteStorage[Player];


	//Failsafe incase the programmer forgets the parentScene
	if (parentScene == nullptr) {
		cc.log(error, "You forgot the parentScene for the Player");
		return false;
	}

	return true;
}

void PlayerBody::HandleEvents(const SDL_Event& event) {
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	//movement controls
	if (canMove) {
		//resets the input each frame
		movement = Vec3();
		if (keyStates[SDL_SCANCODE_W] == 1) { movement.y += 1.0f; }
		if (keyStates[SDL_SCANCODE_S] == 1) { movement.y -= 1.0f; }
		if (keyStates[SDL_SCANCODE_A] == 1) { movement.x -= 1.0f; }
		if (keyStates[SDL_SCANCODE_D] == 1) { movement.x += 1.0f; }

		//if the movement keys are pressed, move the player
		if (VMath::mag(movement) > VERY_SMALL) {
			playerDirection = movement;
		}
		else {
			//Otherwise, set the state to idle
			if (currentState != attack) {
				currentState = idle;
			}

		}
	}

	//dash controls
	if (keyStates[SDL_SCANCODE_SPACE] == 1 && currentState != dash && (!dash_cooldown->hasStarted || dash_cooldown->completed)) {
		currentState = dash;
		dash_timer->Start();
	}

	//melee controls
	if (SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT && currentState == idle) {
			currentState = attack;
			//std::cout << "Pressed left\n";
		}
	}

	//Switching abilities
	if (currentState != attack) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_J:
			selectedAbilities = melee;
			break;

		case SDL_SCANCODE_K:
			selectedAbilities = shoot;
			break;

		case SDL_SCANCODE_L:
			isShielding = !isShielding;
			selectedAbilities = shield;
			break;
		}
	}
}

void PlayerBody::Update(float deltaTime) {
	updateMouseDir(); //Update the melee hitbox
	updateMeleeHitbox(); //Gets the direction of the mouse relative to the player's position

	//If the destroy flag has been set, the player is now dead
	if (currentHealth <= 0) { std::cout << "YOU ARE DEAD \n"; }

	//state machine
	switch (currentState) {
	case idle:
		state_idle();
		break;

	case dash:
		state_dash(deltaTime);
		drawShield = false;
		break;

	case attack:
		state_attack(deltaTime);
		break;

	}

	//update the cooldown timers
	//The difference between the timers in the update pool and the ones that aren't
	//Is that the ones in the update pool don't have a callback, I.e. run this piece of code once it's completed
	//-Adriel
	for (Clock* cd : cooldowns) {
		cd->Update(deltaTime);
		if (cd->completed) { cd->Reset(); }
	}

	//Updating the invincible timer
	if (invincible) {
		invincible_timer->Update(deltaTime);
		if (invincible_timer->completed) {
			invincible = false;
			invincible_timer->Reset();
		}
	}

	//Updating the drawMelee timer
	if (drawMelee) {
		drawMelee_timer->Update(deltaTime);
		if (drawMelee_timer->completed) {
			drawMelee = false;
			drawMelee_timer->Reset();
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
	Body::Update(deltaTime);
}

void PlayerBody::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {
	//Drawing the melee sprite
	if (drawMelee) {
		SDL_Rect Rect{ meleeHitbox->x, meleeHitbox->y,64, 64};
		SDL_RenderCopy(parentScene->getRenderer(), playerSpriteSheet.texture, &playerSpriteSheet.spriteStorage[ouch], &Rect);
	}
	
	//Drawing the shield sprite
	if (drawShield) {
		SDL_Rect Rect{ meleeHitbox->x, meleeHitbox->y,64, 64 };
		SDL_RenderCopy(parentScene->getRenderer(), playerSpriteSheet.texture, &playerSpriteSheet.spriteStorage[melee_strike], &Rect);
	}

	Body::Render(renderer_, projectionMatrix_);
}

void PlayerBody::RenderHitbox(SDL_Renderer* renderer_) {
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

void PlayerBody::OnDestroy() {
	//Cleanup stuff
	for (Clock* item : cooldowns) { delete item; }
	cooldowns.clear();
	dash_timer = nullptr;
	dash_cooldown = nullptr;

	delete dash_timer;
	delete invincible_timer;
	delete drawMelee_timer;

	Body::OnDestroy();
}

PlayerBody::~PlayerBody() {
	OnDestroy();
}

void PlayerBody::updateMouseDir() {
	//Gets the mouse position in physics space
	//Then calculates the normal from the player
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
	//From the mouse direction, sets the hitbox location in screenSpace
	Matrix4 projectionMat = parentScene->getProjectionMatrix();
	Vec3 hitboxPos = Vec3(
		pos.x + (mouseDirection.x * (meleeHitbox->w + 32.0f)),
		pos.y + (mouseDirection.y * (meleeHitbox->h + 32.0f)),
		0.0f
	);
	Vec3 hitboxPosScreen = projectionMat * hitboxPos;
	meleeHitbox->x = hitboxPosScreen.x - meleeHitbox->w * 0.5f;
	meleeHitbox->y = hitboxPosScreen.y - meleeHitbox->h * 0.5f;
}

void PlayerBody::takeDamage(float amount) {
	//Guard clauses
	//If the player is invincible or is dead, just exit 
	if (invincible) { return; }
	if (amount == 0) return;

	currentHealth -= amount - ((amount * (playerDefense / 100)) * 0.8);
	std::cout << "Player took damage\n";
	invincible_timer->Start();
	invincible = true;
}

std::string PlayerBody::getSelectedAbility() const {
	//For the tracker in the scene
	switch (selectedAbilities) {
	case melee:
		return "melee";
	case shoot:
		return "shoot";
	case shield:
		return "shield";
	}
}


#pragma region State methods
void PlayerBody::state_idle() { canMove = true;}

void PlayerBody::state_dash(float deltaTime_) {
	canMove = false; //disables the player's movement input
	dash_timer->Update(deltaTime_);

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
}

void PlayerBody::state_attack(float deltaTime_) {
	switch (selectedAbilities) {
	case melee:{
		//Stops the shield sprite from rendering
		//Yes, this is a hotfix -Adriel
		drawShield = false;

		//Draw the melee sprite only when we haven't done it yet
		if (!drawMelee) { 
			drawMelee = true;
			drawMelee_timer->Start();
		}

		//Check for all the bodies in the scene and comparing it to the melee hitbox
		for (Body* other : parentLevel->levelBodies) {
			if (other->type == PLAYER) { continue; } // skip the player
			if (other->getHitbox()->collisionCheck(meleeHitbox)) {  //if the melee hitbox hits the otherBody hitbox
				if (other->type == SOLID) { std::cout << "You hit a solid\n"; }	//on hit solid,pretty much useless -Adriel
				if (other->type == ENEMY) {		//on hit enemy
					std::cout << "You hit an enemy\n";
					other->takeDamage(meleePower);
				}
			}
		}
		currentState = idle;
		break;
	}

	case shoot: {
		//Yes, this is a hotfix again -Adriel
		drawShield = false;

		//cooldown check! (if its on cooldown, leave)
		if (!shooting_cooldown->hasStarted || shooting_cooldown->completed) {
			shooting_cooldown->Start(); // start the cooldown timer
			//create a new bullet projectile
			Vec3 bulletStartPosition = parentScene->getInverseMatrix() * Vec3(meleeHitbox->x, meleeHitbox->y, 0.0f);
			Projectile* bullet = new Projectile(
				parentLevel,
				bulletStartPosition,
				mouseDirection * projectileSpeed,
				Vec3(0.3f, 0.3f, 0.3f),
				128 * 0.3f, 128 * 0.3f,
				1.0f,
				projectilePower
			);
			//add it to all spawned objects (to be pushed to levelObjects pool)
			parentLevel->spawningBodies.push_back(bullet);
			bullet = nullptr;
		}
		currentState = idle;
		break;
	}

	case shield: {
		drawShield = true;

		//	for all bodies within the level scene
		for (Body* other : parentLevel->levelBodies) {
			if (other->type == PLAYER) { continue; } // skip the player
			if (other->getHitbox()->collisionCheck(meleeHitbox)) {  //	if the melee hitbox hits the otherBody hitbox
				if (other->type == ENEMY) {		//on hit enemy
					//std::cout << "Attacking\n";
					//cout << "shielding against an enemy\n";
					if (!isShielding) playerDefense = 75.0f;
					if (isShielding) playerDefense = playerDefenseDefault;

					//Basically the same collsion response code as the solid
					Vec3 otherVel = other->getVel();
					Vec3 otherPos = other->getPos();

					Vec3 newPos = otherPos + -1 * otherVel * deltaTime_;
					other->setPos(newPos);
					other->setVel(Vec3());

				}
			}
		}
		break;
	}
	}
}

#pragma endregion
