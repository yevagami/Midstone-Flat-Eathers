#ifndef BASICLEVEL_H
#define BASICLEVEL_H
#include "Solid.h"
#include "PlayerBody.h"

class Level{

private:
	Scene* parentScene;
	PlayerBody* player = nullptr;

public:
	//The vectors where all the bodies will be stored and updated and destroyed 
	//"Aka the mortuary" -Diana Astafyeva
	std::vector<Body*>levelBodies;
	std::vector<Body*>trashBodies;

	//Constructors
	Level(PlayerBody* p) { player = p; }

	//Fundamental methods (create, update, render, handle input, destroy)
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;

	virtual Scene* getParentScene() { return parentScene; };
	virtual void setParentScene(Scene* currentScene) { parentScene = currentScene; };
};
#endif