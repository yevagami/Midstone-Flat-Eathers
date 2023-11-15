#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(Level* parentLevel_, Vec3 pos_, subType type_) {
	parentLevel = parentLevel_;
	pos = pos_;
	currentHealth = enemyDefintions[type_].health;
	maxHealth = currentHealth;
	enemyMoveSpeed = enemyDefintions[type_].moveSpeed;
	enemyPower = enemyDefintions[type_].power;
	image = enemyDefintions[type_].image;
	texture = SDL_CreateTextureFromSurface(parentLevel->getParentScene()->getRenderer(), image);
	type = ENEMY;
	Body::LoadHitbox(enemyDefintions[type_].w, enemyDefintions[type_].h);
}

void Enemy::Update(float time){
	//Technically is redundant, because the Body::update is called anyways
	//But I wanna make sure that checking if it should be destroyed is the first thing
	//Because it can exit early
	if (destroyFlag) {
		parentLevel->trashBodies.push_back(this);
		return;
	}

	switch (currentState) {
	case idle:
		state_idle();
		break;

	case followPlayer:
		state_followPlayer();
		break;

	case walk:

		break;
	}

	Body::Update(time);
}

void Enemy::OnCollide(Body* other, float deltaTime){
	if (other->type == PLAYER) {
		other->takeDamage(enemyPower);
	}
}

void Enemy::OnDestroy(){
	playerReference = nullptr;
	Body::OnDestroy();
}

void Enemy::takeDamage(float amount){
	if (amount == 0) return;

	currentHealth -= amount;
	if (currentHealth <= 0) { destroyFlag = true; }
}

void Enemy::state_idle(){
	//Find the player and set it to the playerReference if not already
	if (playerReference == nullptr) {
		for (Body* body : parentLevel->levelBodies) {
			if (body->type == PLAYER) {
				playerReference = body;
			}
		}
	}
	else {
		currentState = followPlayer;
	}
}

void Enemy::state_walk(){

}

void Enemy::state_followPlayer(){
	//If it hasn't found the player yet, go to the idle state and find them
	if (playerReference == nullptr) {
		currentState = idle;
		return;
	}

	//Moves towards the player
	Vec3 playerDirection = VMath::normalize(playerReference->getPos() - pos);
	vel = playerDirection * enemyMoveSpeed;
}
