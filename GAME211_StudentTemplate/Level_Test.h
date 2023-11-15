#pragma once
#include "Level.h"
#include "Solid.h"
#include "Enemy.h"
#include <cstdlib>
#include <ctime>
class Level_test : public Level{
private:
	//Background
	SDL_Texture* background = nullptr;
	//Floor
	Body* floor = nullptr;

public:

	int enemycounter = 0;
	Level_test(Scene* parentScene_) : Level(parentScene_) {}
	void mobSpawner(); //Method that spawns the enemies
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_);
	void HandleEvents(const SDL_Event& event);
};

