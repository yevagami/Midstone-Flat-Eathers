#include "SceneUI.h"
using namespace ui;

#include "EntityMap.h"
EntityMap euiMap; 



SceneUI::SceneUI(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	///	button time
	auto BUTTON_BACKGROUND = ui::SDL_COLOR_MYSTIC_PURPLE; auto BUTTON_TEXT = ui::SDL_COLOR_BLACK; auto rectangle = SDL_Rect{ 0,0,325,75 }; auto square = ui::SDL_Square;
	auto BUTTON_HOVERBACKGROUND = ui::SDL_COLOR_GRAY; auto BUTTON_BORDER = SDL_COLOR_DARK_GRAY;
	auto TEXT_TEXT = ui::SDL_COLOR_ROSE_TOY;

	///	Step 1: Create the Buttons with Initial Values
	mySceneName = new Button(Font{ "UI scene", 45, fontMap.at("comic serif") }, {}, Colour{ SDL_COLOR_NULL, TEXT_TEXT, SDL_COLOR_NULL });

	//how to make it NOT change the color when cursor on top of it??
	playersHPBar = new Button(	//	
		Font{ " players HP here", 30, fontMap.at("comic serif") },
		rectangle,
		Colour{ ui::SDL_COLOR_AMBER_STREAM, BUTTON_TEXT, ui::SDL_COLOR_BLACK, ui::SDL_COLOR_AMBER_STREAM });

	mySmallButton = new Button(	//
		Font{ ":)", 55, fontMap.at("comic serif"),0,0,90 },
		square,
		Colour{ BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND });

	//	grouping for mass attrbute changing, deleting and rendering
	allButtons.emplace_back(mySceneName); //	text
	allButtons.emplace_back(playersHPBar);	//	lowkey the layering (who's rendered on top)
	allButtons.emplace_back(mySmallButton);


	//1.1 individial changes before grouping
	mySmallButton->scaleDimensions(50);
	mySmallButton->isPrideful = true;		//	changes colour on click
	playersHPBar->isTogglable = false;
	mySceneName->textColour = mySceneName->textColour << SDL_White75;


	///	Step 2: Aesthetics
	for (auto* button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	mySceneName->offsetPosition(-300);	//	offsets the text up
	playersHPBar->offsetPosition(-300, 500);
	//	cornering 
	mySmallButton->setPosition(SCREEN_HEIGHT - mySmallButton->getH(), SCREEN_WIDTH - mySmallButton->getW()); //	places the square button into the top corner
	
	isBopping = true;
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
	// we dont need that -scott
	//shut up scott -Adriel
	for (auto* button : allButtons) { button->generateHitbox(); }
	level_1 = new Level1(this);
	level_1->OnCreate();

	return true;
}


void SceneUI::OnDestroy() {
	for (auto* button : allButtons) { delete button; }

	level_1->OnDestroy();
	delete level_1;
}


void SceneUI::Update(const float deltaTime) {

}


void SceneUI::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	level_1->Render(renderer, projectionMatrix);

	//	render the buttons
	for (auto* button : allButtons) { button->Render(renderer); }

	SDL_RenderPresent(renderer);
}


void SceneUI::HandleEvents(const SDL_Event& event_) {
	PrettyPrinting::printMouseCoords(event_);
	for (const auto button : allButtons) { button->HandleEvents(event_); }

	switch (event_.key.keysym.scancode) {
	case SDLK_ESCAPE || SDLK_p:
		pauseMenuOpen = !pauseMenuOpen;
		break;

	default:
		break;
	}


	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);
}