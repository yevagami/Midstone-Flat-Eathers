#include "SceneUI.h"
#include "PrettyPrinting.h"
#include "ConsistentConsole.h"
using namespace ui;

ConsistentConsole ccui;
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
	name = "SceneUI"; // we dont need that 

	//		button showcase
	///	step 3: Hitbox and OnLeftClick

	for (auto* button : allButtons) { button->generateHitbox(); } //	we're going this in the OnCreate because the hitbox needs to be generated after repositioning. this ensures that

	//	what happens when each button is clicked?
	

	//mySmallButton->SetOnLeftClick([&] {ccui.consoleManager(update, "small pressed"); sound.playSound("my bike", false); });
	
	return true;
}


void SceneUI::OnDestroy() {
	for (auto* button : allButtons) { delete button; }
}


void SceneUI::Update(const float deltaTime) {
	// Update player
	//game->getPlayer()->Update(deltaTime);


}


void SceneUI::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//	render the buttons
	for (auto* button : allButtons) { button->Render(renderer); }


	//random blur test code (doesnt work) >:(
	//auto* myBody = new Body(Transform{});
	//myBody->setImage(IMG_Load("Textures/test.png"));
	//// create a surface for the blurred texture
	//SDL_Surface* blurredSurface = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
	//// downscale the image
	//SDL_SoftStretch(myBody->getImage(), nullptr, blurredSurface, nullptr);
	//// create a texture from the blurred surface
	//SDL_Texture* blurredTexture = SDL_CreateTextureFromSurface(renderer, blurredSurface);
	//SDL_FreeSurface(blurredSurface);
	//// set the blend mode for the blurred texture
	//SDL_SetTextureBlendMode(blurredTexture, SDL_BLENDMODE_ADD);
	//SDL_Rect rooct = { 200, 200, 200, 200 };
	//SDL_RenderCopy(renderer, blurredTexture, nullptr, &rooct);

	// render the player
	//game->RenderPlayer(0.1f);


	SDL_RenderPresent(renderer);
}


void SceneUI::HandleEvents(const SDL_Event& event) {
	PrettyPrinting::printMouseCoords(event);
	for (const auto button : allButtons) { button->HandleEvents(event); }



	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);

#pragma region debuggingKeys
	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN) {
		///	CONSOLE TESTING
		//	console messages display: how to call the method
		ccui.consoleManager(error, "error: this is an error message");
		ccui.consoleManager(warning, "warning: this is a warning message");
		ccui.consoleManager(update, "update: this is an update message");
		ccui.consoleManager(not_error, "this is not an error");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN) {
		using namespace ui;

		ccui.consoleManager(update, "toggling all button visibility");
		for (auto button : allButtons) {
			bool state = button->isActive;
			button->isActive = !state;
		}

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {
	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN) {
		PrettyPrinting::printVS(euiMap.findEntitiesByData(string("dog")));
		PrettyPrinting::printVS(euiMap.findEntitiesByData(string("meow")));
	}


	if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN) {
		///	ENTITY MAP TESTING
		//	to insert into an entit map...
		euiMap.insertEntity(string("rex"), string("is my dog"));
		euiMap.insertEntity(string("deedee"), string("was my dog ;-;"));
		euiMap.insertEntity(string("turnip"), string("is my cat"));
		euiMap.insertEntity(string("adriel"), string("is adriel"));
		//	DELETING the test entity
		euiMap.removeEntity(string("test"));
		//	printing...
		PrettyPrinting::printEM(euiMap);
		//	to serialize that entity map...
		euiMap.saveEntityMapToFile("SaveData/entitymap.txt");
	}
#pragma endregion
}
