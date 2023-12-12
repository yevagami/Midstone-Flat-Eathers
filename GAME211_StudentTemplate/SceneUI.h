#ifndef SCENEUI_H
#define SCENEUI_H

#include <MMath.h>
#include "Scene.h"
#include <vector>


#include "Menu.h"

class GameManager;

using namespace ui;
//using namespace MATH;

class SceneUI : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()


	Button* shhh;

	vector<Button*> allButtons;
	Button* button1;
	Button* button2;
	//Button*button3;

	vector<Button*> allTexts;
	Button* text1;
	Button* text2;
	Button* text3;

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	SceneUI(SDL_Window* sdlWindow, GameManager* game_);
	~SceneUI();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event_);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	SDL_Renderer* getRenderer() { return renderer; }

};
#endif