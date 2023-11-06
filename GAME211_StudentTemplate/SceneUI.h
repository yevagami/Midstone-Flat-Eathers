#ifndef SCENEUI_H
#define SCENEUI_H

#include <MMath.h>
#include "Scene.h"
#include <vector>
#include "Menu.h"
#include "Audio.h"

using namespace MATH;

class SceneUI : public Scene
{
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()

public:
	bool isBopping;

	ui::Button* myJankyText;
	ui::Button* myJankySubText;
	ui::Button* myCreditingText;
	ui::Button* myStartButton;
	ui::Button* myOptionsButton;
	ui::Button* myExitButton;
	ui::Button* mySmallButton;
	ui::Button* myDebugButton;
	ui::Button* playersHPBar;


	ui::Button* buttonWithBkgImg;

	ui::Button* mySpookyButton;
	bool bTestMenu;

	//	soon will just be the UIManager
	std::vector<ui::Button*> allButtons; // for making buttons using "Menu.h" **NOT UIMANAGER**

	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	SceneUI(SDL_Window* sdlWindow, GameManager* game_);
	~SceneUI();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	SDL_Renderer* getRenderer() { return renderer; }

};
#endif