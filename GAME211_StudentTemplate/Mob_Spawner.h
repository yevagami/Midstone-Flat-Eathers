#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"


class Mob_Spawner {
	//	a reference to the level this spawner exists in
	Level* parentLevel;

	//	number of mobs spawned per wave
	int mobsPerWave = 10;
	//	is the wave completed?
	bool waveCompleted = false;
	//	current wave
	int currentWave = 0;
	//	has the wave started?
	bool waveStarted = false;

public:
	SDL_Rect spawnBounds;
	bool levelWon = false;
	int enemiesOnTheLevel = 0;
	int enemiesKilled = 0;
	Mob_Spawner(Level* parentLevel_);

	Enemy::subType randomEnemy();
	void mobSpawner(int maxSpawns_, Enemy::subType subType_, SDL_Rect spawnBounds);
	void waveSpawner(int maxWaves_);
	bool gameCompleted() { return levelWon; }
};

