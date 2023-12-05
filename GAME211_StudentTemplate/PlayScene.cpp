#include "PlayScene.h"

PlayScene::PlayScene(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1366.0f;
	yAxis = 768.0f;
	player = nullptr;
	currentLevel = nullptr;
}

bool PlayScene::OnCreate() {
	//SDL window stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	//Set the name of the scene for organizing purposes
	name = "Play Scene";

	//	load trackers
	tracker.scary();


	//	USER INTERFACE
	CreatePauseMenu();
	GUI();


	//Creating the level
	currentLevel = new Level_test(this);
	


	if (!currentLevel->OnCreate()) {
		std::cout << "Something went wrong with the Level\n";
	}

	//Creating the player body
	player = new PlayerBody(
		this,
		Vec3(xAxis * 0.5f, yAxis * 0.5f, 0.0f),
		Vec3(1.0f, 1.0f, 1.0f),
		128.0f,
		128.0f
	);

	if (!player->OnCreate()) {
		std::cout << "Something went wrong with the Player object\n";
		return false;
	};

	//Attaching the playerbody to the level's vector so it can interact with the objects there
	player->setParentLevel(currentLevel);
	currentLevel->levelBodies.push_back(player);

	return true;
}

void PlayScene::OnDestroy() {
	currentLevel->OnDestroy();
	delete currentLevel;

	tracker.unscary();

	player->OnDestroy();
	delete player;
}

void PlayScene::Update(const float time) {

	if (currentLevel->canSwitchTheScene) {
		//switch scenes here
		std::cout << "Scene switched\n";
	}

	if (isPaused == false && isDead == false) {
		currentLevel->Update(time);
	}

	
	if(isDead == true && hasGameoverHappened == false) {
		sfxSound.playSound("gameover");
		hasGameoverHappened = true;
	}


	int enemycounter = 0;
	//Keeps track how many enemies are in the level
	for (auto enemy : currentLevel->levelBodies) {
		if (enemy->type == Body::ENEMY) {
			enemycounter++;
		}
	} std::string enemyCountString = std::to_string(enemycounter);


	///	Trackers [DEBUG THINGS]
	//	"P to Pause"
	tracker.trackThis("P to Pause", tracker.tracker1);

	//max fps showing
	const string fpsString = std::to_string(settings::FPS) + " fps";
	tracker.trackThis(fpsString, tracker.tracker2);





	///	MENU / USER INTERFACE [ trackers, but live ]
	const std::string healthTrackerString = std::to_string(static_cast<int>(round(player->getCurrentHealth())));

	UI_health->text = healthTrackerString;
	if (std::stoi(healthTrackerString) > player->getMaxHealth() / 2 && std::stoi(healthTrackerString) <= player->getMaxHealth()) {
		UI_health->textColour = ui::SDL_COLOR_DARK_GREEN;
	}

	if (std::stoi(healthTrackerString) > 20 && std::stoi(healthTrackerString) <= player->getMaxHealth() / 2) {
		UI_health->textColour = ui::SDL_COLOR_BANANA_YELLOW;
	}
	
	if (std::stoi(healthTrackerString) <= 20) {
		UI_health->textColour = ui::SDL_COLOR_ROSE_TOY;
	}

	const std::string abilityTrackerString = player->getSelectedAbility(); //Keeps track on the ability that the player is using
	UI_abilityText->text = abilityTrackerString;
	if (abilityTrackerString == "melee") {
		//UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/childeicken.jpg";
		UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/sword.png";
	}
	else if (abilityTrackerString == "shoot") {
		//UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/kleelegs.jpg";
		UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/gun.png";
	}
	else if (abilityTrackerString == "shield") {
		//UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/baldzhongli.jpg";
		UI_abilitySprite->backgroundImageDirectory = "Textures/programmer_art/shield.png";
	}



	if(player->getCurrentHealth() == 0.0f) {
		//isDead = true;
		cc.log(update, "you died lmao");
	}


	//	pause menu things
	if(isPaused) {
		soundButtonText1->text = std::to_string(settings::MasterVolume);
		soundButtonText2->text = std::to_string(settings::MusicVolume);
		soundButtonText3->text = std::to_string(settings::SoundEffectVolume);
	}

}


void PlayScene::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	CameraFollowPlayer(player); //Make the camera follow the player
	currentLevel->Render(renderer, projectionMatrix);

	//render the trackers
	tracker.render(renderer);

	//	gui
	for(auto element : allUIElements) {
		element->Render(renderer);
	}

	//	pause menu
	if (isPaused) {
		//	main pause menu
		for (const auto button : allPauseMenuButtons) {
			button->Render(renderer);
		}

		//sub pause buttons
		if (settingsOpen) {
			for (const auto button : allSubPauseMenuButtons) {
				button->Render(renderer);
		}

			//sound menu buttons
			if(soundMenuOpen) {
				soundButtonText1->setPositionRelativeTo(*soundButton1, 50, -75);
				soundButtonText2->setPositionRelativeTo(*soundButton2, 50, -75);
				soundButtonText3->setPositionRelativeTo(*soundButton3, 50, -75);

				for (const auto button : allSoundMenuButtons) {
					button->Render(renderer);
				}
			}

			//	cheat buttons
			if (cheatsOpen) {
				for (const auto button : allCheatMenuButtons) {
					button->Render(renderer);
				}
			}
		}

	}

	SDL_RenderPresent(renderer);
}

void PlayScene::HandleEvents(const SDL_Event& event) {

	if (!isPaused) {
		player->HandleEvents(event);

	}

	if (event.type == SDL_KEYDOWN) {
		//	keyboard event checking
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_P:
			isPaused = !isPaused;
			break;

		case SDL_SCANCODE_0:
			ChangeLevel(new Level2(this));
			break;

		case SDL_SCANCODE_9:
			ChangeLevel(new Level_test(this));
			break;
		}
	}


	if (isPaused) {
		for (const auto button : allPauseMenuButtons) {
			button->HandleEvents(event);
		}
		for (const auto button : allSubPauseMenuButtons) {
			button->HandleEvents(event);
		}
		for (const auto button : allCheatMenuButtons) {
			button->HandleEvents(event);
		}
		for (const auto button : allSoundMenuButtons) {
			button->HandleEvents(event);
		}
	}

	for (auto element : allUIElements) {
		element->HandleEvents(event);
	}
}

void PlayScene::ChangeLevel(Level* newLevel_) {
	//Destroys the level
	currentLevel->OnDestroy();
	delete currentLevel;

	//Set the new level to be the current level
	currentLevel = newLevel_;

	//Throw the player into the new level
	player->setParentLevel(newLevel_);
	currentLevel->levelBodies.push_back(player);
}

void PlayScene::CameraFollowPlayer(PlayerBody* p) {
	//guard clause to make sure the player exists
	if (p == nullptr) {
		return;
		std::cout << "Player doesn't exist\n";
	}

	//move the camera update
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);

	float left = p->getPos().x - xAxis / 2.0f;
	float right = p->getPos().x + xAxis / 2.0f;
	float top = p->getPos().y - yAxis / 2.0f;
	float bottom = p->getPos().y + yAxis / 2.0f;

	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);
}


