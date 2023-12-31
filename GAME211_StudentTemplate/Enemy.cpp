#include "Enemy.h"
#include "Level.h"
#include "PlayerBody.h"
#include <random>

Enemy::Enemy(Level* parentLevel_, Vec3 pos_, subType type_) {
	parentLevel = parentLevel_;
	pos = pos_;
	currentHealth = enemyDefintions[type_].health;
	enemyMoveSpeed = enemyDefintions[type_].moveSpeed;
	enemyPower = enemyDefintions[type_].power;
	image = IMG_Load(enemyDefintions[type_].imagePath.c_str());
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

	float angle = atan2f(vel.y, vel.x);
	angle = angle * 180.0f / M_PI;
	flip = (angle > 90.0f || angle < -90.0f) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

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
	if (OnHurt) OnHurt(); 

	if (currentHealth <= 0) {
		if (OnDeath) OnDeath(); 

		destroyFlag = true;
		
		if (playerReference != nullptr) {
			playerReference->killCount += 1;
			playerReference->points += 100;
		}

		SpawnDrops();
	}
}

void Enemy::SetOnDeath(const std::function<void()>& onDeath_) { OnDeath = onDeath_; }
void Enemy::SetOnHurt(const std::function<void()>& onOuchie_) { OnHurt = onOuchie_; }

void Enemy::state_idle(){
	//Find the player and set it to the playerReference if not already
	if (playerReference == nullptr) {
		for (Body* body : parentLevel->levelBodies) {
			if (body->type == PLAYER) {
				playerReference = dynamic_cast<PlayerBody*>(body);
			}
		}
	}
	
	//If the distance between the player and the enemy is larget than x
	//We ignore them
	if (VMath::mag(playerReference->getPos() - pos) < enemyChaseDistance ) {
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

	if (VMath::mag(playerReference->getPos() - pos) > enemyChaseDistance) {
		currentState = idle;
		return;
	}

	//Moves towards the player
	Vec3 playerDirection = VMath::normalize(playerReference->getPos() - pos);
	vel = playerDirection * enemyMoveSpeed;
}

void Enemy::SpawnDrops() {
	//This is chat GPT code (yes I know)
	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> distribution(0, maxDrops);
	int amountToDrop = distribution(gen);

	float scale = 0.3f;
	Drop* healthDrop;
	for (int i = 0; i < amountToDrop; i++) {
		std::uniform_int_distribution<int> distribution(1, 3);
		int whatToDrop = distribution(gen);
		Drop::DropType whatWeDropping = (whatToDrop == 3) ? Drop::DropType::HEALTH : Drop::DropType::POINTS;

		int randomX = distribution(gen);
		int randomY = distribution(gen);

		healthDrop = new Drop(parentLevel, pos + Vec3(randomX * 20.0f, randomY * 20.0f, 0.0f), Vec3(scale, scale, scale), 128 * scale, 128 * scale, whatWeDropping);
		parentLevel->spawningBodies.push_back(healthDrop);
	}
	healthDrop = nullptr;
}
