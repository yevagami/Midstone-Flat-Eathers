#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"
#include "Mob_Spawner.h" 

class Level_MainMenu : public Level{
private:


public:
	//Mob_Spawner* newMobSpawner = new Mob_Spawner(this);
	Level_MainMenu(Scene* parentScene_) : Level(parentScene_) {}

	//Method that spawns the enemies
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time_) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
	void HandleEvents(const SDL_Event& event_) override;
	
};

