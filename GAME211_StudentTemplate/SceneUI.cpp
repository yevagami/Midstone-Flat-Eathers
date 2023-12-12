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
	text2 = new Button(Font{ "credits", 50 });

	allTexts.emplace_back(text1);

	for (const auto text : allTexts) {
		text->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		text->textColour = SDL_COLOR_ANTIQUE_WHITE;
		text->isTextBordered = true;
	}
	text1->offsetPosition(-300);


	//	the buttons
	button1 = new Button(Font{ "Play Game" }, SDL_Testangle, Colour{});
	button2 = new Button(Font{ "Quit Game" }, SDL_Testangle, Colour{});
	//button3 = new Button(Font{}, SDL_Testangle, Colour{});

	allButtons.emplace_back(button1);
	allButtons.emplace_back(button2);


	for (const auto button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		button->backgroundColour = SDL_COLOR_FOREST_GREEN;
		button->buttonBorderColour = SDL_COLOR_BLACK;

		button->SetOnInteractionCallback([&]() {
			sfxSound.playSound("select");
		});
	}
	button1->offsetPosition(-100);
	button2->setPositionRelativeTo(*button1, 150);

	button1->SetOnLeftClick([&]() {
		cc.log(debug, "in game theory this should send us to a dif level");
		isGameStarted = true;
		});

	button2->SetOnLeftClick([&]() {
		cc.log(debug, "quit game");

		game->StartFadeInTransition(1000,
			[&]() { GameManager::quitPls(); },
			[&]() { GameManager::savePls(); });
		});


	//	the background lmao
	shhh = new Button(Font{}, SDL_Testangle);
	shhh->backgroundColour = SDL_COLOR_SLATE_BLUE;
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


}


void SceneUI::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	shhh->Render(renderer);

	for (const auto& text : allTexts) {
		text->Render(renderer);
	}

	for (const auto& button : allButtons) {
		button->Render(renderer);
	}



	SDL_RenderPresent(renderer);
}


void SceneUI::HandleEvents(const SDL_Event& event_) {

	for (const auto button : allButtons) {
		button->HandleEvents(event_);
	}


	switch (event_.key.keysym.scancode) {



	default:
		break;
	}

}