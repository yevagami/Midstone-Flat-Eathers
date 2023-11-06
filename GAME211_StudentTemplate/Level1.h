#ifndef LEVEL1_H
#define LEVEL1_H


#include "BasicLevel.h"
#include "Solid.h"
#include "PlayerBody.h"
class Level1 : BasicLevel{
private: 
	float xAxis;
	float yAxis;
	SDL_Window* window;
	GameManager* game;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

public:
	PlayerBody* player;
	void CameraFollowPlayer(PlayerBody* p);

	//Scene objects
	std::vector<Body*>sceneObjects;
	std::vector<Body*>trashObjects;

	//Constructor
	Level1(SDL_Window* sdlWindow_, GameManager* game_);
	~Level1();

	//Fundamental methods (create, update, render, handle input, destroy)
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);

	//getters and setters
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	SDL_Renderer* getRenderer() { return renderer; }

};
#endif