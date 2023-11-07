#pragma once
#include "Scene.h"
#include "PlayerBody.h"

class PlayScene : public Scene{
private:
	float xAxis;
	float yAxis;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

public:
	PlayerBody* player = nullptr;
	void CameraFollowPlayer(PlayerBody* p);

	//Constructor/destructors
	PlayScene(SDL_Window* sdlWindow_, GameManager* game_);
	~PlayScene();

};

