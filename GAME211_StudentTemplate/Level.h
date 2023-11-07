#ifndef LEVEL_H
#define LEVEL_H
#include "Solid.h"
#include "PlayerBody.h"

class Scene;
class Level{
protected:
	Scene* parentScene = nullptr;

public:
	Level(Scene* parentScene_) { parentScene = parentScene_; }
	//The vectors where all the bodies will be stored and updated and destroyed 
	//"Aka the mortuary" -Diana Astafyeva
	std::vector<Body*>levelBodies;
	std::vector<Body*>trashBodies;

	//Fundamental methods (create, update, render, handle input, destroy)
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
};
#endif