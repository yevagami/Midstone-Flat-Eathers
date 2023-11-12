#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(Level* parentLevel_, Vec3 pos_, subType type_) {
	parentLevel = parentLevel_;
	pos = pos_;
	//player = player_;
	currentHealth = enemyDefintions[type_].health;
	maxHealth = currentHealth;
	moveSpeed = enemyDefintions[type_].moveSpeed;
	power = enemyDefintions[type_].power;
	image = enemyDefintions[type_].image;
	texture = SDL_CreateTextureFromSurface(parentLevel->getParentScene()->getRenderer(), image);
	type = ENEMY;
	Body::LoadHitbox(enemyDefintions[type_].w, enemyDefintions[type_].h);
}