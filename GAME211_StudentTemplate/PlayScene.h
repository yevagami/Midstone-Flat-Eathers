#pragma once
#include "Scene.h"
#include "PlayerBody.h"
#include "Level_test.h"
#include "Menu.h"
#include "Tracker.h"

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
	Tracker tracker;
#pragma endregion

	//Player 
	PlayerBody* player;
	void CameraFollowPlayer(PlayerBody* p); 

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



	//	testing a menu [ has to be at scene level >:( ]
	vector<ui::Button*> allPauseMenuButtons;
	ui::Button* button1;
	ui::Button* button2;
	ui::Button* button3;

	bool isPaused;
	vector<ui::Button*> allSubPauseMenuButtons;
	ui::Button* subButton1;
	ui::Button* subButton2;
	ui::Button* subButton3;

	void CreatePauseMenu() { //Iill move this when it fully works
		button1 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button2 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button3 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});

		allPauseMenuButtons.emplace_back(button1);
		allPauseMenuButtons.emplace_back(button2);
		allPauseMenuButtons.emplace_back(button3);

		subButton1 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		subButton2 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		subButton3 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});

		allSubPauseMenuButtons.emplace_back(subButton1);

		button1->text = "Settings";
		button2->text = "Resume";
		button3->text = "Quit";

		subButton1->text = "fps";


		for (const auto button : allPauseMenuButtons) {
			//	centered
			button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

			//	universal cosmetics
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 2;
		}

		//	On Left Clicks
		//	Settings
		button1->SetOnLeftClick([]() {
			if (settings::FPS == 60) {
				settings::FPS = 30;
			}
			else if (settings::FPS == 30) {
				settings::FPS = 60;
			}
			});

		button1->offsetPosition(0,0);		//	mid
		button2->setPositionRelativeTo(*button1, -100);			//top
		button3->setPositionRelativeTo(*button1, 100);				//	bottom


		//	make them clickable
		for (const auto button : allPauseMenuButtons) { button->generateHitbox(); }
	}

};

