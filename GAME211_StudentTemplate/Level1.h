#ifndef LEVEL1_H
#define LEVEL1_H

#include "Level.h"
#include "Solid.h"
#include "PlayerBody.h"

class Level1 : public Level{
private: 
	SDL_Texture* background = nullptr;

public:
	Level1(Scene* parentScene) : Level(parentScene) { }

	//Scene objects
	std::vector<Body*>sceneObjects;
	std::vector<Body*>trashObjects;

	//Fundamental methods (create, update, render, handle input, destroy)
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time) override;
	void Render() override;
	void HandleEvents(const SDL_Event& event) override;
};
#endif