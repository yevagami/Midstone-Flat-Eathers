#pragma once
#include "Scene.h"
#include "PlayerBody.h"
#include "Level_test.h"
#include "Menu.h"
#include "Tracker.h"

#include "FileManager.h"


class GameManager;

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
	bool isPaused = false;
	vector<ui::Button*> allPauseMenuButtons;
	ui::Button* button1;
	ui::Button* button2;
	ui::Button* button3;

	bool settingsOpen = false;
	vector<ui::Button*> allSubPauseMenuButtons;
	ui::Button* subButton1;
	ui::Button* subButton2;
	ui::Button* subButton3;

	bool cheatsOpen = false;
	vector<ui::Button*> allCheatMenuButtons;
	ui::Button* cheatButton1;
	ui::Button* cheatButton2;
	ui::Button* cheatButton3;

	void CreatePauseMenu() { //I'll move this when it fully works
		//	main pause buttons
		button1 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button2 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button3 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});

		allPauseMenuButtons.emplace_back(button1);
		allPauseMenuButtons.emplace_back(button2);
		allPauseMenuButtons.emplace_back(button3);

		//	sub pause buttons (options menu)
		subButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		subButton2 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		subButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});

		allSubPauseMenuButtons.emplace_back(subButton1);
		allSubPauseMenuButtons.emplace_back(subButton2);
		allSubPauseMenuButtons.emplace_back(subButton3);

		//	cheat pause buttons (cheat menu)
		cheatButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		cheatButton2 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		cheatButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});

		allCheatMenuButtons.emplace_back(cheatButton1);
		allCheatMenuButtons.emplace_back(cheatButton2);
		allCheatMenuButtons.emplace_back(cheatButton3);


		button1->text = "Settings";
		button2->text = "Resume";
		button3->text = "Quit";

		subButton1->text = "FPS";
		subButton2->text = "cheats";
		subButton3->text = "save?";

		cheatButton1->text = "heal";
		cheatButton2->text = "god";
		cheatButton3->text = "";

		for (const auto button : allPauseMenuButtons) {
			//	centered
			button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

			//	universal cosmetics
			button->fontSize = 45;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 2;
		}

		for (const auto button : allSubPauseMenuButtons) {
			button->scaleDimensions(50);
			//	centered
			button->setPositionRelativeTo(*button1, 0, 450);

			//	universal cosmetics
			button->fontSize = 25;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 1;
		}

		for (const auto button : allCheatMenuButtons) {
			button->scaleDimensions(50);
			//	centered
			button->setPositionRelativeTo(*button1, 0, 600);

			//	universal cosmetics
			button->fontSize = 25;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 1;
			//button->isPrideful = true;
		}

		//	On Left Clicks
		//	Settings
		button1->isTogglable = true;
		button1->SetOnLeftClick([&]() {
			cc.log(update, "settings menu toggled");
			//	open settings menu
			if(!button1->isOn) {
				settingsOpen = true;
			}else {
				settingsOpen = false;
			}
			//settingsOpen = !settingsOpen;
			});
		button2->SetOnLeftClick([&]() {
			cc.log(update, "resuming game");
			//	resume game
			isPaused = false;
			//button1->isOn = false;
			//settingsOpen = false;
			//subButton2->isOn = false;
			//cheatsOpen = false;
			});
		button3->SetOnLeftClick([&]() {
			cc.log(update, "quitting game");
			//quit
			isRunning = false;
			

		});

		subButton1->SetOnLeftClick([&]() {
			cc.log(update, "fps changed");
			const int fpsValues[] = { 60, 30, 90 };  // possible FPS values
			const size_t numFPSValues = sizeof(fpsValues) / sizeof(fpsValues[0]);

			for (size_t i = 0; i < numFPSValues; ++i) {
				if (settings::FPS == fpsValues[i]) {
					settings::FPS = fpsValues[(i + numFPSValues - 1) % numFPSValues];
					break;
				}
			}
			});
		subButton1->SetOnRightClick([&]() {
			cc.log(update, "fps changed");
			const int fpsValues[] = { 60, 30, 90 };  // possible FPS values
			const size_t numFPSValues = sizeof(fpsValues) / sizeof(fpsValues[0]);

			for (size_t i = 0; i < numFPSValues; ++i) {
				if (settings::FPS == fpsValues[i]) {
					settings::FPS = fpsValues[(i + 1) % numFPSValues];
					break;
				}
			}
		});
		subButton2->isTogglable = true;
		subButton2->SetOnLeftClick([&]() {
			cc.log(update, "cheat menu toggled");
			if(!subButton2->isOn) {
				cheatsOpen = true;
			}else {
				cheatsOpen = false;
			}
		});
		subButton3->SetOnLeftClick([&]() {
			cc.log(update, "not implemented");

		});

		//	full heal (default on left, max on right)
		cheatButton1->SetOnLeftClick([&]() {
			cc.log(update, "health pack acquired!");
			player->setCurrentHealthToDefault();
		});
		cheatButton1->SetOnRightClick([&]() {
			cc.log(update, "super heath pack acquired!");
			player->setCurrentHealthToMax();
		});
		//	god
		cheatButton2->isTogglable = true;
		cheatButton2->SetOnLeftClick([&]() {
			if(!cheatButton2->isOn) {
				cc.log(update, "ur invincible!");
				player->setCurrentInvincibilityDuration(55555);
				player->setInvincible(true);
			}else {
				cc.log(update, "ur no longer invincible");
				player->setCurrentInvincibilityToDefault();
				player->setInvincible(false);
			}
		});
		cheatButton3->SetOnLeftClick([&]() {

		});



		button1->offsetPosition(0,0);											//	mid
		button2->setPositionRelativeTo(*button1, -100);				//top
		button3->setPositionRelativeTo(*button1, 100);				//	bottom

		subButton1->offsetPosition(0, 0);
		subButton2->offsetPosition(-125);
		subButton3->offsetPosition(125);

		cheatButton1->offsetPosition(0, 0);
		cheatButton2->offsetPosition(-125);
		cheatButton3->offsetPosition(125);

		


		//	make them clickable
		for (const auto button : allPauseMenuButtons) { button->generateHitbox(); }
		for (const auto button : allSubPauseMenuButtons) { button->generateHitbox(); }
		for (const auto button : allCheatMenuButtons) { button->generateHitbox(); }
	}

};

