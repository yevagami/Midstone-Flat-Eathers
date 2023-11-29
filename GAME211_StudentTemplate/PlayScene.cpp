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
	//	testing a menu at scene level
	CreatePauseMenu();


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
	if (isPaused == false) {
		CameraFollowPlayer(player); //Make the camera follow the player
		currentLevel->Update(time);
	}


	//Tracking stuff
	std::string healthTrackerString = std::to_string(int(round(player->getCurrentHealth())));
	int enemycounter = 0;

	//Keeps track how many enemies are in the level
	for (auto enemy : currentLevel->levelBodies) {
		if (enemy->type == Body::ENEMY) {
			enemycounter++;
		}
	}

	std::string enemyCountString = std::to_string(enemycounter);
	std::string abilityTrackerString = player->getSelectedAbility(); //Keeps track on the ability that the player is using

	tracker.trackThis(healthTrackerString, tracker.tracker1);
	if (healthTrackerString > "0") {
		tracker.tracker1->textColour = ui::SDL_COLOR_DARK_GREEN;
	}
	if (healthTrackerString <= "0") {
		tracker.tracker1->textColour = ui::SDL_COLOR_ROSE_TOY;
	}

	tracker.trackThis(enemyCountString, tracker.tracker2);

	tracker.trackThis(abilityTrackerString, tracker.tracker3);
	if (abilityTrackerString == "melee") {
		tracker.tracker3->textColour = ui::SDL_COLOR_BANANA_YELLOW;
	}
	else if (abilityTrackerString == "shoot") {
		tracker.tracker3->textColour = ui::SDL_COLOR_LIGHT_BLUE;
	}
	else if (abilityTrackerString == "shield") {
		tracker.tracker3->textColour = ui::SDL_COLOR_SILVER;
	}
	//max fps showing
	string fpsString;
	fpsString = std::to_string(settings::FPS) + " fps";
	tracker.trackThis(fpsString, tracker.tracker4);

	//	showing pause button
	tracker.trackThis("P to Pause", tracker.tracker5);
	//tracker.tracker5->setPositionRelativeTo(*tracker.tracker1, 0, -400);

	tracker.trackThis(std::to_string(player->getCurrentInvincibilityDuration()), tracker.tracker6);
}


void PlayScene::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	currentLevel->Render(renderer, projectionMatrix);

	//render the trackers
	tracker.render(renderer);

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
	}

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


