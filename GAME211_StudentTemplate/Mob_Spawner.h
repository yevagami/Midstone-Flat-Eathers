#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"
class Mob_Spawner 
{
	Level* parentLevel;

	int mobsPerWave = 10;
	bool waveCompleted = false;
	int currentWave = 0;
	bool waveStarted = false;
public:
	SDL_Rect spawnBounds;
	int enemiesOnTheLevel = 0;
	int enemiesKilled = 0;
	Mob_Spawner(Level* parentLevel_);
	void mobSpawner(int maxSpawns_, Enemy::subType subType_, SDL_Rect spawnBounds);
	void waveSpawner(int maxWaves_);
};

