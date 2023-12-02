#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"
#include <cstdlib>

class Level_test : public Level{
private:
	//Background
	SDL_Texture* background = nullptr;
	//Floor
	Body* floor = nullptr;

public:

	int enemycounter = 0;
	Level_test(Scene* parentScene_) : Level(parentScene_) {}

	//Method that spawns the enemies
	void mobSpawner(const int maxSpawns_ = 5, Enemy::subType subType_ = Enemy::flash) {
		//checks if there is an enemy on the level, if no enemy exit the loop and create one.  
		int enemycounter = 0;
		for (auto enemy : levelBodies) {
			if (enemy->type == Body::ENEMY) {
				enemycounter++;
			}
		}

		//I changed the limit to be 5 so it's more fun :) -Adriel
		if (enemycounter >= maxSpawns_) {
			return;
		}

		//This whole section is made to randomise the position of spawned mob. Yes its an int because rand() wants an int. Sorry.
		int scaryMaxX = (1366.0f / 2.0f) + 128.0f * 4.5f;
		int scaryMaxY = (768.0f / 2.0f) + 128.0f * 4.5f;
		int scaryMinX = (1366.0f / 2.0f) - 128.0f * 4.5f;
		int scaryMinY = (768.0f / 2.0f) - 128.0f * 4.5f;

		Enemy* ghost = new Enemy(this, Vec3((std::rand() % scaryMaxX + scaryMinX), (std::rand() % scaryMaxY + scaryMinY), 0), subType_);
		levelBodies.push_back(ghost);
		ghost = nullptr;
		cc.log(not_error, "Did I come here?");

	}

	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_);
	void HandleEvents(const SDL_Event& event);
};

