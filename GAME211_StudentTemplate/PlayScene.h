#pragma once
#include "Scene.h"
#include "PlayerBody.h"
#include "Level_test.h"
#include "Menu.h"

class PlayScene : public Scene{
private:
	//Basic scene stuff
	float xAxis;
	float yAxis;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	// (can move anywhere with a render)
#pragma region variableTracking
	ui::Button* tracker1;
	ui::Button* tracker2;
	ui::Button* tracker3;
	std::vector<ui::Button*> allTrackers;

	//	init all "trackers" (shh, theyre buttons)
	void scary();
	//	tell a tracker to track a value (do this in update)
	static void trackThis(std::string value_, ui::Button* tracker_);
	//	testing
	static int genRanNum(int min_, int max_);
#pragma endregion

	//Player 
	PlayerBody* player;
	void CameraFollowPlayer(PlayerBody* p);

	//	for enemy ai, for example "if (howClose is more than 5){ enemy.rangedAttack; }"
	int howClose(Body* body_, Body* otherBody_);


	//Level 
	Level* currentLevel;
public:

	//Constructor/destructors
	PlayScene(SDL_Window* sdlWindow_, GameManager* game_);
	~PlayScene(){}

	//Fundamental methods
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

