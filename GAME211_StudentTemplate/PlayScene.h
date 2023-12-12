#pragma once
#include "Scene.h"
#include "PlayerBody.h"
#include "Level_test.h"
#include "Level2.h"
#include "Level_3.h"
#include "Tracker.h"

#include "Menu.h"

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
	std::string currentLevelString;


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


	//Game loop stuff
	bool isDead = false;
	bool hasGameoverHappened = false;
	void ChangeLevel(Level* newLevel_);

	///	menu		 [ has to be at scene level >:( ]
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
	ui::Button* subButton4;

	bool soundMenuOpen = false;
	vector<ui::Button*> allSoundMenuButtons;
	ui::Button* soundButton1;
	ui::Button* soundButton2;
	ui::Button* soundButton3;
	ui::Button* soundButtonText1;
	ui::Button* soundButtonText2;
	ui::Button* soundButtonText3;


	bool cheatsOpen = false;
	vector<ui::Button*> allCheatMenuButtons;
	ui::Button* cheatButton1;
	ui::Button* cheatButton2;
	ui::Button* cheatButton3;

	//I'll move this when it fully works
	void CreatePauseMenu() { 
		//	main pause buttons
		button1 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button2 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});
		button3 = new ui::Button(ui::Font{}, ui::SDL_Testangle, ui::Colour{});

		allPauseMenuButtons.emplace_back(button1);
		allPauseMenuButtons.emplace_back(button2);
		allPauseMenuButtons.emplace_back(button3);

		//	sub pause buttons (pause menu -> options menu)
		subButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		subButton2 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		subButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		subButton4 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});


		allSubPauseMenuButtons.emplace_back(subButton1);
		allSubPauseMenuButtons.emplace_back(subButton2);
		allSubPauseMenuButtons.emplace_back(subButton3);
		allSubPauseMenuButtons.emplace_back(subButton4);


		//	sound changing buttons (pause menu -> sound menu)
		soundButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		soundButton2 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		soundButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		soundButtonText1 = new ui::Button(ui::Font{});
		soundButtonText2 = new ui::Button(ui::Font{});
		soundButtonText3 = new ui::Button(ui::Font{});

		allSoundMenuButtons.emplace_back(soundButton1);
		allSoundMenuButtons.emplace_back(soundButton2);
		allSoundMenuButtons.emplace_back(soundButton3);
		allSoundMenuButtons.emplace_back(soundButtonText1);
		allSoundMenuButtons.emplace_back(soundButtonText2);
		allSoundMenuButtons.emplace_back(soundButtonText3);

		//	cheat pause buttons (pause menu -> options menu -> cheat menu)
		cheatButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		cheatButton2 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
		cheatButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});

		allCheatMenuButtons.emplace_back(cheatButton1);
		allCheatMenuButtons.emplace_back(cheatButton2);
		allCheatMenuButtons.emplace_back(cheatButton3);


		button1->text = "Settings";
		button2->text = "Resume Game";
		button3->text = "Return to Menu";

		subButton1->text = "FPS";
		subButton2->text = "cheats";
		subButton3->text = "save";
		subButton4->text = "sound";

		soundButton1->text = "master";
		soundButton2->text = "music";
		soundButton3->text = "sfx";

		cheatButton1->text = "heal";
		cheatButton2->text = "god";
		cheatButton3->text = "stronk";

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

			//	anything that happens on an interact
			button->SetOnInteractionCallback([&]() {
				sfxSound.playSound("select");
			});

		}

		for (const auto button : allSubPauseMenuButtons) {
			//	change scale (cuz theyre small squares)
			button->scaleDimensions(50);
			//	centered
			button->setPositionRelativeTo(*button1, -12.5, 450);

			//	universal cosmetics
			button->fontSize = 25;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 1;

			//	anything that happens on an interact
			button->SetOnInteractionCallback([&]() {
				sfxSound.playSound("select");
				});

		}
		subButton4->setPositionRelativeTo(*button1, -12.5, -125);

		for (const auto button : allCheatMenuButtons) {
			//	change scale (cuz theyre small squares)
			button->scaleDimensions(50);
			//	centered
			button->setPositionRelativeTo(*button1, -12.5, 600);

			//	universal cosmetics
			button->fontSize = 25;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 1;
			//button->isPrideful = true;

			//	anything that happens on an interact
			button->SetOnInteractionCallback([&]() {
				sfxSound.playSound("select");
				});

		}

		for(const auto button : allSoundMenuButtons) {
			//	change scale (cuz theyre small squares)
			button->scaleDimensions(50);
			//	centered
			button->setPositionRelativeTo(*subButton4,0, -125);

			//	universal cosmetics
			button->fontSize = 25;
			button->isTextBordered = true;
			button->textBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			button->buttonBorderColour = ui::SDL_COLOR_SLATE_GRAY;
			button->buttonBorderSize = 4;
			button->textBorderSize = 1;

			//	anything that happens on an interact
			button->SetOnInteractionCallback([&]() {
				sfxSound.playSound("select");
				});

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
		});

		button2->SetOnLeftClick([&]() {
			cc.log(update, "resuming game");
			isPaused = false;
			});

		button3->SetOnLeftClick([&]() {
			cc.log(update, "quitting game");


			isMainMenuOpen = true;

			//game->StartFadeInTransition(1000,
			//	//	because those GM methods are static, we dont want to call them through a reference, therefore GameManager::
			//	[&]() { GameManager::quitPls();},
			//	[&]() { GameManager::savePls();} );
			
		});

		subButton4->isTogglable = true;
		subButton4->SetOnLeftClick([&]() {
			if (!subButton4->isOn) {
				soundMenuOpen = true;
			} else {
				soundMenuOpen = false;
			}
		});

		subButton1->SetOnLeftClick([&]() {
			cc.log(update, "fps changed");
			constexpr int fpsValues[] = { 30, 60, 90, 120 };  // possible FPS values
			constexpr size_t numFPSValues = std::size(fpsValues);

			for (size_t i = 0; i < numFPSValues; ++i) {
				if (options::FPS == fpsValues[i]) {
					options::FPS = fpsValues[(i + 1) % numFPSValues];
					break;	}	}

			});

		subButton1->SetOnRightClick([&]() {
			cc.log(update, "fps changed");
			constexpr int fpsValues[] = { 30, 60, 90, 120 };  // possible FPS values
			constexpr size_t numFPSValues = std::size(fpsValues);

			for (size_t i = 0; i < numFPSValues; ++i) {
				if (options::FPS == fpsValues[i]) {
					options::FPS = fpsValues[(i + numFPSValues - 1) % numFPSValues];
					break; } }

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
			cc.log(update, "save button pressed");
			options::SaveAllSettigns();
		});

		subButton3->SetOnRightClick([&]() {
			cc.log(update, "default settings applied");
			options::ApplyDefaultSettings();
		});

		//master v0lume
		soundButton1->SetOnLeftClick([&]() {
			options::SetMasterVolume(options::MasterVolume + .10f);
		});
		soundButton1->SetOnRightClick([&]() {
			options::SetMasterVolume(options::MasterVolume - .10f);
		});
		//music volume
		soundButton2->SetOnLeftClick([&]() {
			options::SetMusicVolume(options::MusicVolume + .10f);
		});
		soundButton2->SetOnRightClick([&]() {
			options::SetMusicVolume(options::MusicVolume - .10f);
		});
		//sfx volume
		soundButton3->SetOnLeftClick([&]() {
			options::SetSFXVolume(options::SoundEffectVolume + .10f);
		});
		soundButton3->SetOnRightClick([&]() {
			options::SetSFXVolume(options::SoundEffectVolume - .10f);
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
		cheatButton3->isTogglable = true;
		cheatButton3->SetOnLeftClick([&]() {
			if(!cheatButton3->isOn) {
				constexpr int stronkness = 500;
				player->setCurrentMeleeDamage(stronkness);
				player->setCurrentProjectileDamage(stronkness);
				cc.log(update, "your melee attacks are stronger!", std::to_string(player->getCurrentMeleeDamage()));
				cc.log(update, "your projectiles are stronger!!", std::to_string(player->getCurrentProjectileDamage()));
			} else {
				player->setCurrentMeleeDamageToDefault();
				player->setCurrentProjectileDamageToDefault();
				cc.log(update, "your melee attacks are default", std::to_string(player->getCurrentMeleeDamage()));
				cc.log(update, "your projectiles are default", std::to_string(player->getCurrentProjectileDamage()));
			}
		});
		cheatButton3->SetOnRightClick([&]() {

		});



		button1->offsetPosition(0,0);												//	mid
		button2->setPositionRelativeTo(*button1, -100);													//top
		button3->setPositionRelativeTo(*button1, 100);														//	bottom

		subButton1->offsetPosition(0, 0);
		subButton2->offsetPosition(-125);
		subButton3->offsetPosition(125);

		soundButton1->offsetPosition(0, 0);
		soundButton2->offsetPosition(-125);
		soundButton3->offsetPosition(125);

		cheatButton1->offsetPosition(0, 0);
		cheatButton2->offsetPosition(-125);
		cheatButton3->offsetPosition(125);


		//	make them clickable
		for (const auto button : allPauseMenuButtons) { button->generateHitbox(); }
		for (const auto button : allSubPauseMenuButtons) { button->generateHitbox(); }
		for (const auto button : allSoundMenuButtons) { button->generateHitbox(); }
		for (const auto button : allCheatMenuButtons) { button->generateHitbox(); }
	}


	vector<ui::Button*> allUIElements;
	ui::Button* UI_health;
	ui::Button* UI_abilityText;
	ui::Button* UI_abilitySprite;

	void GUI() {
		UI_health = new ui::Button(ui::Font{"", 35});
		UI_abilitySprite = new ui::Button(ui::Font{}, ui::SDL_Square);
		UI_abilityText = new ui::Button(ui::Font{"", 25});

		allUIElements.emplace_back(UI_health);
		allUIElements.emplace_back(UI_abilitySprite);
		allUIElements.emplace_back(UI_abilityText);

		for(auto element : allUIElements) {
			element->isTextBordered = true;
			element->isSensitiveToHovering = false;
			//element->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

			element->textColour = ui::SDL_COLOR_ANTIQUE_WHITE;
			element->textBorderColour = ui::SDL_COLOR_BLACK;
			element->backgroundColour = ui::SDL_COLOR_DARK_SLATE_GRAY;
			element->buttonBorderColour = ui::SDL_COLOR_BLACK;
			element->buttonBorderSize = 4;
			element->textBorderSize = 2;
		}

		UI_abilitySprite->EnableBackgroundImage();
		UI_abilitySprite->scaleDimensions(50);
		UI_abilitySprite->setPosition(SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100);
		UI_abilityText->setPositionRelativeTo(*UI_abilitySprite, -25, 50);


		UI_health->setPositionRelativeTo(*UI_abilitySprite, -75, 50);
		//UI_health->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		//UI_health->offsetPosition(-SCREEN_HEIGHT + 400);


	}
};

