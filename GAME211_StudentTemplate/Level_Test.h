#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"

class Level_test : public Level{
private:
	//Background
	SDL_Texture* background = nullptr;
	//Floor
	Body* floor = nullptr;

public:

	int enemycounter = 0;
	Level_test(Scene* parentScene_) : Level(parentScene_) {}


	//Trying SDL rect for spawnign 
	SDL_Rect spawnBounds;
	
	//Method that spawns the enemies
	void mobSpawner(const int maxSpawns_ = 5, Enemy::subType subType_ = Enemy::flash, SDL_Rect spawnBounds = SDL_Rect());

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
	void HandleEvents(const SDL_Event& event) override;
};

