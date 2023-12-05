#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"
#include "Mob_Spawner.h" 

class Level_test : public Level{
private:
	//Background
	SDL_Texture* background = nullptr;
	//Floor
	Body* floor = nullptr;


public:
	Mob_Spawner* newMobSpawner = new Mob_Spawner(this);
	Level_test(Scene* parentScene_) : Level(parentScene_) {}

	//Method that spawns the enemies
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
	void HandleEvents(const SDL_Event& event) override;
};

