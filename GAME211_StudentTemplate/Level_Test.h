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
	Level_test(Scene* parentScene_) : Level(parentScene_) {}
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_);
	void HandleEvents(const SDL_Event& event);
};

