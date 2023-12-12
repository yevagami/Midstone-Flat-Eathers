#pragma once
#include "Level.h"
#include "Menu.h"
#include <random>

using namespace ui;

class Level_DeathScreen : public Level {
private:

	std::string randomizeDeathMessage();
	std::string deathString = "";
	bool isDeathScreenHere = false;
	Button* deathText;


public:
	//Mob_Spawner* newMobSpawner = new Mob_Spawner(this);
	Level_DeathScreen(Scene* parentScene_) : Level(parentScene_) {}

	//Method that spawns the enemies
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time_) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
	void HandleEvents(const SDL_Event& event_) override;

};

