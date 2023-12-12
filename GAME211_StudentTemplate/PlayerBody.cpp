#include "PlayerBody.h"
#include "Scene.h"
#include "Level.h"
#include "Projectile.h"
#include "math.h"

bool PlayerBody::OnCreate() {
	//Setting the variables

	//Create the melee hitbox
	meleeHitbox = new Hitbox(98, 98, pos.x, pos.y);

	//Creating timers
	dash_timer = new Clock(dashDuration, false, [this]() {
		if (selectedAbilities == shield) {
			currentState = attack;
		}
		else {
			currentState = idle;
		}
		canMove = true;

		//set the current and max speed;
		currentSpeed = walkSpeed;
		maxSpeed = walkSpeed;

		dash_timer->Reset();
		//vel = Vec3(); //reset the player's speed and set the state to idle
		});
	invincible_timer = new Clock(invincibleDuration, false, [this]() {
		invincible = false;
		invincible_timer->Reset();
		});
	drawAttack_timer = new Clock(drawAttackDuration, false, [this]() {
		drawAttack = false;
		drawAttack_timer->Reset();
		drawShield = false;
		});
	dash_cooldown = new Clock(dashCooldown, false);
	shooting_cooldown = new Clock(shootingCooldown, false);

	//Pushes the timer to the vector
	cooldowns.push_back(drawAttack_timer);
	cooldowns.push_back(dash_timer);
	cooldowns.push_back(dash_cooldown);
	cooldowns.push_back(shooting_cooldown);
	cooldowns.push_back(invincible_timer);

	//set the maxSpeed to the currentSpeed
	currentSpeed = walkSpeed;
	maxSpeed = currentSpeed;
	currentState = idle;

	//Load the player sprite sheet
	playerSpriteSheet = Sprite("Textures/programmer_art/player_sheet_final.png", parentScene->getRenderer());
	if (!playerSpriteSheet.autoLoadSprites()) {
		std::cout << "Error in the sprite sheet\n";
		return false;
	}
	image = playerSpriteSheet.image;
	texture = playerSpriteSheet.texture;
	currentSprite = playerSpriteSheet.spriteStorage[Player_Down];

	effectSpriteSheet = Sprite("Textures/programmer_art/player_effects_sheet.png", parentScene->getRenderer());
	if (!effectSpriteSheet.autoLoadSprites()) {
		std::cout << "Error in the effect sprite sheet\n";
		return false;
	}

	//Failsafe incase the programmer forgets the parentScene
	if (parentScene == nullptr) {
		cc.log(error, "You forgot the parentScene for the Player");
		return false;
	}

	//Loads the sprite animations
	LoadAnimations();

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

	//attack controlls
	if (event.key.repeat == 0 && event.type == SDL_MOUSEBUTTONDOWN) {
		if (currentState == idle) {
			currentState = attack;
		}
		
		//For some reason this thing broke again
		//So I fixed it using a delay that is used for drawing the other animations on screen
		//Cause I don't want to make a new timer
		//This is the Nuclear fix 
		//Hope it doesn't break
		if (selectedAbilities == shield) {
			if (!drawShield) {
				isShielding = true;
				cout << isShielding << endl;
				sfxSound.playSound("shield");
				currentState =  attack;

			}
			else {
				isShielding = false;
				cout << isShielding << endl;
				sfxSound.playSound("shield");
				currentState = idle;
			}
		}
		//std::cout << "Pressed left\n";
	}

	//Switching abilities
	if (event.type == SDL_KEYDOWN) { //	KEY DOWN ONLY
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_J:
			sfxSound.playSound("equip"); //	debug sound effect
			selectedAbilities = melee;
			break;

		case SDL_SCANCODE_K:
			sfxSound.playSound("equip"); //	debug sound effect
			selectedAbilities = shoot;
			break;

		case SDL_SCANCODE_L:
			sfxSound.playSound("equip"); //	debug sound effect
			selectedAbilities = shield;
			break;

		} 
	} 
}

void PlayerBody::Update(float deltaTime) {
	
	updateMouseDir(); //Update the melee hitbox
	updateMeleeHitbox(); //Gets the direction of the mouse relative to the player's position

	//If the destroy flag has been set, the player is now dead

	//FOR NOW REMOVED
	//if (currentHealth <= 0) { std::cout << "YOU ARE DEAD \n"; }

	//state machine
	switch (currentState) {
	case idle:
		state_idle();
		break;

	case dash:
		state_dash(deltaTime);
		isShielding = false;
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

	//Update the animation controller
	animController->UpdateAnimationController(deltaTime);
	attackAnimController->UpdateAnimationController(deltaTime);
}

void PlayerBody::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {
	//Get the angle to face the direction of the mouse
	Vec3 meleeRectInScreen = parentScene->getProjectionMatrix() * Vec3();
	SDL_Rect meleeRect{ meleeHitbox->x, meleeHitbox->y, 98, 98 };
	float angle = atan2f(mouseDirection.y, mouseDirection.x);
	angle = angle * 180 / 3.14159;


	if (drawAttack) {
		switch (selectedAbilities) {
		case melee:
			attackAnimController->PlayAnimation(anim_slash);
			break;
		case shoot:
			attackAnimController->PlayAnimation(anim_shoot);
			break;
		}
	}
	else {
		switch (selectedAbilities) {
		case melee:
			attackAnimController->PlayAnimation(anim_sword);
			break;
		case shoot:
			attackAnimController->PlayAnimation(anim_gun);
			break;
		}
	}

	
	attackAnimCutout = attackAnimController->GetCurrentFrame();
	SDL_RendererFlip flip = (angle > 90.0f || angle < -90.0f) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
	
	if (selectedAbilities != shield) {
		SDL_RenderCopyEx(parentScene->getRenderer(), effectSpriteSheet.texture, attackAnimCutout, &meleeRect, -angle, nullptr, flip);
	}
	if (isShielding) {
		attackAnimController->PlayAnimation(anim_shield);
		SDL_RenderCopyEx(parentScene->getRenderer(), effectSpriteSheet.texture, attackAnimController->GetCurrentFrame(), &meleeRect, -angle, nullptr, flip);
	}
	
	

#pragma region Animation stuff
	//Switching the animations that are being played depending on the direction and the state
	//If you are moving, your animations will also move
	if (VMath::mag(vel) > 0.001) {
		//Up
		if (playerDirection.x == 0 && playerDirection.y == 1) {
			animController->PlayAnimation(anim_walk_up);
		}
		//Down
		if (playerDirection.x == 0 && playerDirection.y == -1) {
			animController->PlayAnimation(anim_walk_down);
		}

		//Left
		if (playerDirection.x == -1 && playerDirection.y == 0) {
			animController->PlayAnimation(anim_walk_left);
		}

		//Right
		if (playerDirection.x == 1 && playerDirection.y == 0) {
			animController->PlayAnimation(anim_walk_right);
		}
	}
	else {
		//Up
		if (playerDirection.x == 0 && playerDirection.y == 1) {
			animController->PlayAnimation(anim_up);
		}
		//Down
		if (playerDirection.x == 0 && playerDirection.y == -1) {
			animController->PlayAnimation(anim_down);
		}

		//Left
		if (playerDirection.x == -1 && playerDirection.y == 0) {
			animController->PlayAnimation(anim_left);
		}

		//Right
		if (playerDirection.x == 1 && playerDirection.y == 0) {
			animController->PlayAnimation(anim_right);
		}
	}
#pragma endregion

	//The cutout sets which 
	cutout = animController->GetCurrentFrame();
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

	//Deleting the animation controllers
	delete animController;
	delete attackAnimController;

	cc.log(update, "Deleting PlayerBody");

	Body::OnDestroy();

	//Cleanup for the sprites and animations
	//Note: no need to call on destroy on the player's sprite since the player already points to the object and Body::ondestroy() already destroys that 
	//playerSpriteSheet.onDestroy();
	effectSpriteSheet.onDestroy();
}


PlayerBody::~PlayerBody() {
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
		pos.x + (mouseDirection.x * (meleeHitbox->w + 16.0f)),
		pos.y + (mouseDirection.y * (meleeHitbox->h + 16.0f)),
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

	const double damageTaken = amount - ((amount * (playerDefence / 100)) * 0.8);
	currentHealth -= static_cast<float>(damageTaken);

	if (currentHealth < 0) {
		currentHealth = 0; // ensure currentHealth doesn't go below 0
	}

	cc.log(not_error, "player took damage", std::to_string(damageTaken));
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
void PlayerBody::state_idle() { canMove = true; }

void PlayerBody::state_dash(float deltaTime_) {
	isShielding = false;

	canMove = false; //disables the player's movement input

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
}

void PlayerBody::state_attack(float deltaTime_) {
	switch (selectedAbilities) {
	case melee: {
		sfxSound.playSound("slash");
		//Stops the shield sprite from rendering
		//Yes, this is a hotfix -Adriel
		if (isShielding) {
			isShielding = false;
		}

		//Draw the melee sprite only when we haven't done it yet
		if (!drawAttack) {
			drawAttack = true;
			drawAttack_timer->Start();
		}

		//Check for all the bodies in the scene and comparing it to the melee hitbox
		for (Body* other : parentLevel->levelBodies) {
			if (other->type == PLAYER) { continue; } // skip the player
			if (other->getHitbox()->collisionCheck(meleeHitbox)) {  //if the melee hitbox hits the otherBody hitbox
				if (other->type == SOLID) { cc.log(not_error, "you hit a solid"); }	//on hit solid,pretty much useless -Adriel
				if (other->type == ENEMY) {		//on hit enemy
					//cc.log(not_error, "you hit an enemy!");
					other->takeDamage(getCurrentMeleeDamage());
				}
			}
		}
		currentState = idle;
		break;
	}

	case shoot: {
		sfxSound.playSound("gunshot");
		//Yes, this is a hotfix again -Adriel
		if (isShielding) {
			isShielding = false;
		}

		if (!drawAttack) {
			drawAttack = true;
			drawAttack_timer->Start();
		}

		//cooldown check! (if its on cooldown, leave)
		if (!shooting_cooldown->hasStarted || shooting_cooldown->completed) {
			shooting_cooldown->Start(); // start the cooldown timer
			//create a new bullet projectile
			Vec3 bulletStartPosition = parentScene->getInverseMatrix() * Vec3(meleeHitbox->x, meleeHitbox->y, 0.0f);
			
			Projectile* bullet = new Projectile(
				parentLevel,
				bulletStartPosition,
				mouseDirection * projectileSpeed,
				Vec3(1.0f, 1.0f, 1.0f),
				128 * 0.3f, 128 * 0.3f,
				1.0f,
				getCurrentProjectileDamage()
			);
			if (VMath::mag(mouseDirection * projectileSpeed) <= 0) {
				cout << "Huh???\n";
			}
			//add it to all spawned objects (to be pushed to levelObjects pool)
			parentLevel->spawningBodies.push_back(bullet);
			bullet = nullptr;
		}
		currentState = idle;
		break;
	}

	case shield: {
		if (isShielding) {
			drawShield = true;
			if (!drawAttack) {
				drawAttack = true;
				drawAttack_timer->Start();
			}

			setCurrentDefence(playerDefenceShielded);
			//sfxSound.playSound("slash"); // ear destroying

			for (Body* other : parentLevel->levelBodies) {
				if (other->type == PLAYER) { continue; } // skip the player
				if (other->getHitbox()->collisionCheck(meleeHitbox)) {  //	if the melee hitbox hits the otherBody hitbox
					if (other->type == ENEMY) {		//on hit enemy
						//std::cout << "Attacking\n";
						//Basically the same collsion response code as the solid
						Vec3 otherVel = other->getVel();
						Vec3 otherPos = other->getPos();

						Vec3 newPos = otherPos + -1 * otherVel * deltaTime_;
						other->setPos(newPos);
						other->setVel(Vec3());

					}
				}
			}
		}
		else {
			setCurrentDefenceToDefault();
		}
		break;
	}
	}
}
#pragma endregion

void PlayerBody::LoadAnimations() {
	//Create an animation controller
	animController = new AnimationController();
	attackAnimController = new AnimationController();

	//Load the walking animations

	//Left
	Sprite temp = Sprite("Textures/programmer_art/player_sheet_final.png", parentScene->getRenderer());
	if (!temp.loadSpriteFromRectInARow(128, 128 * Player_Left, 128, 128, 6)) { cout << "Left sprite did not load properly" << endl; return;};
	anim_walk_left = Animation("player_walk_left", temp.spriteStorage, 0.1f, 6, true);
	anim_left = Animation("player_left", SDL_Rect{ 0, 128 * Player_Left, 128, 128 }, 0.0f, 0, false);
	temp.deleteSprites();

	//Right
	if (!temp.loadSpriteFromRectInARow(128, 128 * Player_Right, 128, 128, 6)) { cout << "Right sprite did not load properly" << endl; return; };
	anim_walk_right = Animation("player_walk_right", temp.spriteStorage, 0.1f, 6, true);
	anim_right = Animation("player_right", SDL_Rect{ 0, 128 * Player_Right, 128, 128 }, 0.0f, 0, false);
	temp.deleteSprites();

	//Up
	if (!temp.loadSpriteFromRectInARow(128, 128 * Player_Up, 128, 128, 6)) { cout << "Up sprite did not load properly" << endl; return; };
	anim_walk_up = Animation("player_walk_up", temp.spriteStorage, 0.1f, 6, true);
	anim_up = Animation("player_up", SDL_Rect{ 0, 128 * Player_Up, 128, 128 }, 0.0f, 0, false);
	temp.deleteSprites();

	//Down
	if (!temp.loadSpriteFromRectInARow(128, 128 * Player_Down, 128, 128, 6)) { cout << "Down sprite did not load properly" << endl; return; };
	anim_walk_down = Animation("player_walk_down", temp.spriteStorage, 0.1f, 6, true);
	anim_down = Animation("player_down", SDL_Rect{ 0, 128 * Player_Down, 128, 128 }, 0.0f, 0, false);
	temp.deleteSprites();

	//This is called to cleanup the SDL_Surface and SDL_Texture
	temp.onDestroy();

	//Load the static sprites
	temp = Sprite("Textures/programmer_art/player_effects_sheet.png", parentScene->getRenderer());
	if(!temp.autoLoadSprites()) { cc.log(error, "Effects sheet fail to load"); return; }
	anim_sword = Animation("player_sword", temp.spriteStorage[Sword], 0.0f, 0.0f, false);
	anim_gun = Animation("player_gun", temp.spriteStorage[Gun], 0.0f, 0.0f, false);
	anim_shield = Animation("player_shield", temp.spriteStorage[Shield], 0.0f, 0.0f, false);
	temp.deleteSprites();

	//Load the slash sprite
	if (!temp.loadSpriteFromRectInARow(0, 128, 128, 128, 5)) { cout << "Slash sprite did not load properly" << endl; return; };
	anim_slash = Animation("player_sword_slash", temp.spriteStorage, 0.1f, 5, true);
	temp.deleteSprites();

	//Load the shooting sprite
	if (!temp.loadSpriteFromRectInARow(0, 128 * Gun, 128, 128, 4)) { cout << "Gun sprite did not load properly" << endl; return; };
	anim_shoot = Animation("player_gun_shoot", temp.spriteStorage, 0.15f, 4, true);
	temp.deleteSprites();
	
	temp.onDestroy();

	//By default the player looks up
	animController->PlayAnimation(anim_up);

	//By default the player has the sword
	attackAnimController->PlayAnimation(anim_sword);
}