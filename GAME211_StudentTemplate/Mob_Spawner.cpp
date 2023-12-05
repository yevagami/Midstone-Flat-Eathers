#include "Mob_Spawner.h"
#include <random>

Mob_Spawner::Mob_Spawner(Level* parentLevel_) {
	parentLevel = parentLevel_;
	spawnBounds = { static_cast<int>((1366.0f / 2.0f) - 128.0f * 4.5f),
							static_cast<int>((768.0f / 2.0f) - 128.0f * 4.5f),
							static_cast<int>(128.0f * 9.0f),
							static_cast<int>(128.0f * 9.0f) };
}

Enemy::subType Mob_Spawner::randomEnemy() {
	//	create a random device for generating numbers
	std::random_device rd;
	// use the Mersenne Twister engine with the random device as a seed
	std::mt19937 gen(rd());

	//	define the range of subtypes using the first and last subtype values
	int min_ = static_cast<int>(Enemy::subType::FIRST_SUBTYPE);
	int max_ = static_cast<int>(Enemy::subType::LAST_SUBTYPE);

	// apply a uniform distribution to generate a random value within the subtype range
	std::uniform_int_distribution<> distrib(min_, max_);

	// generate a random subtype value
	int randomValue = distrib(gen);

	// convert the random value back to the subType enum
	return static_cast<Enemy::subType>(randomValue);
}

void Mob_Spawner::mobSpawner(int maxSpawns_, Enemy::subType subType_, SDL_Rect spawnBounds) {

	Vec3 spawnPosition = {
		   static_cast<float>(std::rand() % spawnBounds.w + spawnBounds.x),
		   static_cast<float>(std::rand() % spawnBounds.h + spawnBounds.y),
		   0.0f };
	//checks if there is an enemy on the level, if no enemy exit the loop and create one.  
	int enemycounter = 0;
	for (auto enemy : parentLevel->levelBodies) {
		if (enemy->type == Body::ENEMY) {
			enemycounter++;
		}
	}
	//I changed the limit to be 5 so it's more fun :) -Adriel
	if (enemycounter >= maxSpawns_) {
		return;
	}

	std::cout << enemiesOnTheLevel << endl;
	Enemy* ghost = new Enemy(parentLevel, spawnPosition, subType_);
	parentLevel->levelBodies.push_back(ghost);
	ghost = nullptr;


}
void Mob_Spawner::waveSpawner(int maxWaves_) {

	if ((waveCompleted || !waveStarted) && currentWave < maxWaves_) {
		cout << "NEW WAVE BABY!!!\n";
		currentWave++;
		for (int i = 0; i < mobsPerWave; i++) {
			mobSpawner(mobsPerWave, Enemy::flash, spawnBounds);
		}
		waveStarted = true;
		waveCompleted = false;
	}
	//Check if wave has been cleared
	//Check if the amount of enemies in the level is 0
	//therefore a wave has been cleared
	int enemycounter = 0;
	for (auto enemy : parentLevel->levelBodies) {
		if (enemy->type == Body::ENEMY) {
			enemycounter++;
		}
	}

	if (enemycounter <= 0) { waveCompleted = true; }
}
