#ifndef LEVEL_H
#define LEVEL_H
#include "Solid.h"
#include "PlayerBody.h"


class Scene;
class Level{
protected:
	Scene* parentScene = nullptr;

public:
	bool canSwitchTheScene = false; //flag to tell the Scene to change the level
	Level(Scene* parentScene_) { parentScene = parentScene_; }
	//The vectors where all the bodies will be stored and updated and destroyed 
	//"Aka the mortuary" -Diana Astafyeva
	std::vector<Body*>levelBodies;
	std::vector<Body*>trashBodies;
	std::vector<Body*>spawningBodies; //I'm adding this vector because std::vector doesn't like it when you try to push_back() something to the vector while iterating through it

	//Fundamental methods (create, update, render, handle input, destroy)
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) = 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;

	Scene* getParentScene() { return parentScene; }
	void setParentScene(Scene* parentScene_) { parentScene = parentScene_; }
};
#endif