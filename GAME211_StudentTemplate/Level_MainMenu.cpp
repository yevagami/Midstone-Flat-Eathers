#include "Level_MainMenu.h"


bool Level_MainMenu::OnCreate(){


	//	the text
	text1 = new Button(Font{"ur mom is !!FLAT!!", 100});
	text2 = new Button(Font{"credits", 50});

	allTexts.emplace_back(text1);

	for (const auto text : allTexts) {
		text->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		text->textColour = SDL_COLOR_ANTIQUE_WHITE;
		text->isTextBordered = true;
	}
	text1->offsetPosition(-300);


	//	the buttons
	button1 = new Button(Font{"Play Game"}, SDL_Testangle, Colour{});
	button2 = new Button(Font{"Quit Game"}, SDL_Testangle, Colour{});
	//button3 = new Button(Font{}, SDL_Testangle, Colour{});

	allButtons.emplace_back(button1);
	allButtons.emplace_back(button2);


	for(const auto button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

		button->backgroundColour = SDL_COLOR_FOREST_GREEN;
		button->buttonBorderColour = SDL_COLOR_BLACK;

	}
	button1->offsetPosition(-100);
	button2->setPositionRelativeTo(*button1, 150);

	button1->SetOnLeftClick([&]() {
		cc.log(debug, "in game theory this should send us to a dif level");
	});

	button2->SetOnLeftClick([&]() {
		cc.log(debug, "quit game");

		
		parentScene->game->StartFadeInTransition(1000,
			[&]() { GameManager::quitPls(); },
			[&]() { GameManager::savePls(); });
	});


	//	the background lmao
	shhh = new Button(Font{}, SDL_Testangle);
	shhh->backgroundColour = SDL_COLOR_ROSE_TOY;
	shhh->offsetPosition(-10, -10);
	shhh->scaleDimensionsIndividually(11, 11);



	for(const auto button : allButtons) { button->generateHitbox(); }

	return true;
}


void Level_MainMenu::OnDestroy(){

	for(const auto& button : allButtons) {
		delete button;
	}




	//Destroys everything except the player
	for (Body* body : levelBodies) {
		if (body->type == body->PLAYER) {
			body = nullptr;
			continue;
		}
		body->OnDestroy();
		delete body;
	}

	levelBodies.clear();
}


void Level_MainMenu::Update(const float time_){

	if (!menuMusicSound.isPlayingExperimental()) {

		menuMusicSound.playSound("main menu", true);
		//playRandomMusic();
	}


	for (const auto& button : allButtons) {
		button->Update(time_);
	}
	

}

void Level_MainMenu::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){

	shhh->Render(renderer_);

	for(const auto& text : allTexts) {
		text->Render(renderer_);
	}

	for (const auto& button : allButtons) {
		button->Render(renderer_);
	}


}

void Level_MainMenu::HandleEvents(const SDL_Event& event_){

	for(const auto button : allButtons) {
		button->HandleEvents(event_);
	}


}
