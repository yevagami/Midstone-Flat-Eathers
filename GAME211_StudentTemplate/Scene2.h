#include "Menu.h"
#include "Scene.h"
#include "Solid.h"
#include "PlayerBody.h"

class Scene2 : public Scene{
private:
	float xAxis;	
	float yAxis;
	SDL_Window* window;		
	SDL_Renderer* renderer;	
	Matrix4 projectionMatrix;	
	Matrix4 inverseProjection;	

public:
	//Player related stuff
//Solid* block;
	PlayerBody* player;
	void CameraFollowPlayer(PlayerBody* p);

	//Scene objects
	std::vector<Body*>sceneObjects;
	std::vector<Body*>trashObjects;

	//UI stuff
	ui::Button* scene2Button;
	std::vector<ui::Button*> allButtons; // for making buttons using "Menu.h" **NOT UIMANAGER**

	//Constructor
	Scene2(SDL_Window* sdlWindow_, GameManager* game_);
	~Scene2();
	
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

