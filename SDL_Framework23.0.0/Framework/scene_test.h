#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "Body.h"
#include "Player.h"
#include <vector>
#include <string>
#include "Save.h"

#include "Save.h"

using namespace std;
class scene_test : public Scene{
	//Name of the scene for organizing stuff
	std::string sceneName = "scene_test";

	//SDL window stuff
	SDL_Window* window;
	int screenWidth, screenHeight, screenDepth;
	int virtualWidth, virtualHeight, virtualDepth;

	SDL_Renderer* screenRenderer;

	// Bodies in the scene
	Body* background;
	Body* notThePlayer;
	Player* player;
	vector<Body*>bodyObjects;

	//Texture loading methods
	SDL_Texture* loadImage(const char* textureFile);
	SDL_Rect scale(SDL_Texture* objectTexture,
		int start_x = 0, int start_y = 0, float scale = 1.0f);

public:
	//Constructor/destructor
	scene_test(SDL_Window* sdlWindow);
	~scene_test();

	bool OnCreate();
	void HandleEvents(const SDL_Event& sdlEvent);
	void Update(const float time);
	void Render();
	void OnDestroy();

	//Methods
	Vec3 PhysicsSpaceToScreenSpace(Vec3 physicsCoords);
};

