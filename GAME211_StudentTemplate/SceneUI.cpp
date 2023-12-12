#include "SceneUI.h"


SceneUI::SceneUI(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = static_cast<float>(SCREEN_WIDTH);
	yAxis = static_cast<float>(SCREEN_HEIGHT);

}


SceneUI::~SceneUI() = default;


bool SceneUI::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "SceneUI";
	isMainMenuOpen = true;
	isGameStarted = false;


	//	the text
	text1 = new Button(Font{ "the world is !!FLAT!!", 100 });
	text2 = new Button(Font{ "Adriel, Michael, Diana, Helen", 25 });

	allTexts.emplace_back(text1);
	allTexts.emplace_back(text2);

	for (const auto& text : allTexts) {
		text->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		text->textColour = SDL_COLOR_ANTIQUE_WHITE;
		text->isTextBordered = true;
	}

	text1->offsetPosition(-285);
	text2->setPositionRelativeTo(*text1, 55);


	//	the buttons
	PlayButton = new Button(Font{ "Play Game" }, SDL_Testangle, Colour{});
	QuitButton = new Button(Font{ "Quit Game" }, SDL_Testangle, Colour{});
	SettingsButton = new Button{ Font{"Settings"}, SDL_Testangle, Colour{} };

	allButtons.emplace_back(PlayButton);
	allButtons.emplace_back(QuitButton);
	allButtons.emplace_back(SettingsButton);


	for (const auto& button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		button->backgroundColour = SDL_COLOR_FOREST_GREEN;
		button->buttonBorderColour = SDL_COLOR_BLACK;

		button->SetOnInteractionCallback([&]() {
			sfxSound.playSound("select");
			});
	}
	PlayButton->setPositionRelativeTo(*SettingsButton, -100);
	SettingsButton->offsetPosition();
	QuitButton->setPositionRelativeTo(*SettingsButton, 100);

	PlayButton->SetOnLeftClick([&]() {
		cc.log(debug, "in game theory this should send us to a dif level");
		isGameStarted = true;
		});

	SettingsButton->isTogglable = true;
	SettingsButton->SetOnLeftClick([&]() {

		if(!SettingsButton->isOn) {
			cc.log(debug, "settings menu opened");
			settingsOpen = true;
		}else {
			cc.log(debug, "settings menu closed");
			settingsOpen = false;
		}
	});


	QuitButton->SetOnLeftClick([&]() {
		cc.log(debug, "quit game");

		game->StartFadeInTransition(1000,
			[&]() { GameManager::quitPls(); },
			[&]() { GameManager::savePls(); });
		});


	//	sub pause buttons (pause menu -> options menu)
	subButton1 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
	subButton3 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});
	subButton4 = new ui::Button(ui::Font{}, ui::SDL_Square, ui::Colour{});


	allSubPauseMenuButtons.emplace_back(subButton1);
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

	subButton1->text = "FPS";
	subButton3->text = "save";
	subButton4->text = "sound";

	soundButton1->text = "master";
	soundButton2->text = "music";
	soundButton3->text = "sfx";


	for (const auto button : allSubPauseMenuButtons) {
		//	change scale (cuz theyre small squares)
		button->scaleDimensions(50);
		//	centered
		button->setPositionRelativeTo(*SettingsButton, -12.5, 450);

		//	universal cosmetics
		button->fontSize = 25;
		button->isTextBordered = true;
		button->backgroundColour = SDL_COLOR_FOREST_GREEN;
		button->buttonBorderColour = SDL_COLOR_BLACK;
		button->textBorderColour = ui::SDL_COLOR_BLACK;
		button->buttonBorderSize = 4;
		button->textBorderSize = 1;

		//	anything that happens on an interact
		button->SetOnInteractionCallback([&]() {
			sfxSound.playSound("select");
			});

	}
	subButton4->setPositionRelativeTo(*SettingsButton, -12.5, -125);


	for (const auto button : allSoundMenuButtons) {
		//	change scale (cuz theyre small squares)
		button->scaleDimensions(50);
		//	centered
		button->setPositionRelativeTo(*subButton4, 0, -125);

		//	universal cosmetics
		button->fontSize = 25;
		button->isTextBordered = true;
		button->backgroundColour = SDL_COLOR_FOREST_GREEN;
		button->buttonBorderColour = SDL_COLOR_BLACK;
		button->textBorderColour = ui::SDL_COLOR_BLACK;
		button->buttonBorderSize = 4;
		button->textBorderSize = 1;

		//	anything that happens on an interact
		button->SetOnInteractionCallback([&]() {
			sfxSound.playSound("select");
			});

	}

	subButton4->isTogglable = true;
	subButton4->SetOnLeftClick([&]() {
		if (!subButton4->isOn) {
			soundMenuOpen = true;
		}
		else {
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
				break;
			}
		}

		});

	subButton1->SetOnRightClick([&]() {
		cc.log(update, "fps changed");
		constexpr int fpsValues[] = { 30, 60, 90, 120 };  // possible FPS values
		constexpr size_t numFPSValues = std::size(fpsValues);

		for (size_t i = 0; i < numFPSValues; ++i) {
			if (options::FPS == fpsValues[i]) {
				options::FPS = fpsValues[(i + numFPSValues - 1) % numFPSValues];
				break;
			}
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



	subButton1->setPositionRelativeTo(*SettingsButton, -75, 450);
	subButton3->setPositionRelativeTo(*SettingsButton, 75, 450);

	//subButton1->offsetPosition(0, 0);
	//subButton3->offsetPosition(125);

	soundButton1->offsetPosition(0, 0);
	soundButton2->offsetPosition(-125);
	soundButton3->offsetPosition(125);



	//	make them clickable
	for (const auto button : allSubPauseMenuButtons) { button->generateHitbox(); }
	for (const auto button : allSoundMenuButtons) { button->generateHitbox(); }



	//	the background lmao
	shhh = new Button(Font{}, SDL_Testangle);
	shhh->isButtonBordered = false;
	shhh->backgroundColour = SDL_COLOR_GOLDEN_STREAM / SDL_COLOR_BLACK;
	shhh->offsetPosition(-10, -10);
	shhh->scaleDimensionsIndividually(11, 11);



	for (const auto button : allButtons) { button->generateHitbox(); }


	return true;
}


void SceneUI::OnDestroy() {


	for (const auto& button : allButtons) {
		delete button;
	}

	for(const auto& text : allTexts) {
		delete text;
	}


}


void SceneUI::Update(const float deltaTime_) {

	if (!menuMusicSound.isPlayingExperimental() && options::MusicVolume >= 0.1) {
		GameManager::playRandomMusic(menuMusicSound);
	}


	for (const auto& button : allButtons) {
		button->Update(deltaTime_);
	}


	if (soundMenuOpen) {

		soundButtonText1->text = std::to_string(options::MasterVolume);
		soundButtonText2->text = std::to_string(options::MusicVolume);
		soundButtonText3->text = std::to_string(options::SoundEffectVolume);

		soundButtonText1->setPositionRelativeTo(*soundButton1, 50, -75);
		soundButtonText2->setPositionRelativeTo(*soundButton2, 50, -75);
		soundButtonText3->setPositionRelativeTo(*soundButton3, 50, -75);

	}


}


void SceneUI::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	shhh->Render(renderer);

	for (const auto& text : allTexts) {
		text->Render(renderer);
	}

	if(settingsOpen) {
		for (const auto& button : allSubPauseMenuButtons) {
			button->Render(renderer); }
	}

	if(soundMenuOpen && settingsOpen) {
		for (const auto& button : allSoundMenuButtons) {
			button->Render(renderer);
		}
	}
	
	for (const auto& button : allButtons) {
		button->Render(renderer);
	}



	SDL_RenderPresent(renderer);
}


void SceneUI::HandleEvents(const SDL_Event& event_) {

	for (const auto& button : allButtons) {
		button->HandleEvents(event_);
	}

	if(settingsOpen) {
		for (const auto& button : allSubPauseMenuButtons) {
			button->HandleEvents(event_);
		}
	}

	if(soundMenuOpen) {
		for (const auto& button : allSoundMenuButtons) {
			button->HandleEvents(event_);
		}

	}
	

}