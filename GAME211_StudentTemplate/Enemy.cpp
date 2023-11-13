#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(Level* parentLevel_, Vec3 pos_, subType type_) {
	parentLevel = parentLevel_;
	pos = pos_;
	//player = player_;
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
	if (destroyFlag) {
		parentLevel->trashBodies.push_back(this);
		return;
	}
	Body::Update(time);
}

void Enemy::OnCollide(Body* other, float deltaTime){
	if (other->type == PLAYER) {
		other->takeDamage(enemyPower);
	}
}

void Enemy::OnDestroy(){
	player = nullptr;
	Body::OnDestroy();
}

void Enemy::takeDamage(float amount){
	currentHealth -= amount;
	if (currentHealth <= 0) { destroyFlag = true; }
}
