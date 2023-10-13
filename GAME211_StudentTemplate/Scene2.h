#pragma once
#include "Menu.h"
#include "Scene.h"

class Scene2 : public Scene{
private:
	Body* block;

	float xAxis;	
	float yAxis;
	SDL_Window* window;		
	SDL_Renderer* renderer;	
	Matrix4 projectionMatrix;	
	Matrix4 inverseProjection;	

public:

	std::vector<ui::Button*> allButtons; // for making buttons using "Menu.h" **NOT UIMANAGER**


	Scene2(SDL_Window* sdlWindow_, GameManager* game_);
	~Scene2();
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
};

