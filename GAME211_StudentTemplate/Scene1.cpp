#include "Scene1.h"
#include "PrettyPrinting.h"
#include "ConsistentConsole.h"




//a global var. My problem was that i defined it in the Scene 3 again, that made a linking error.
//IMPORTANT!!!
ConsistentConsole cc; //not member of scene1 class. Define somewhere else 
#include "EntityMap.h"
EntityMap eMap; //not member of scene1 class




// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;


}


Scene1::~Scene1() = default;


bool Scene1::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "scene1"; // we dont need that 
				//	ew^

	//	button showcase
	using namespace ui;	auto BUTTON_BACKGROUND = SDL_COLOR_SOUL_CAMPFIRE; auto BUTTON_TEXT = SDL_COLOR_BLACK; auto rectangle = SDL_Testangle; auto square = SDL_Square;
	auto BUTTON_HOVERBACKGROUND = SDL_COLOR_ROSE_TOY;

	///	Step 1: Create the Buttons with Default Values

	auto* myJankyText = new Button(Font{"ur amazing<3", 100, fontMap.at("comic serif")});
	auto* myJankySubText = new Button(Font{"with rizz", 25, fontMap.at("comic serif"),0,0,-45.0});
	auto* myCreditingText = new Button(Font{ "Adriel, Michael, Diana, and Helen", 25, fontMap.at("comic serif")});

	auto* myStartButton = new Button(	//	
		Font{ "start button", 50, fontMap.at("comic serif") },
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myOptionsButton = new Button(	//	
		Font{ "options button", 50, fontMap.at("comic serif") },
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myExitButton = new Button(	//	
		Font{ "exit button", 50, fontMap.at("comic serif") },
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* mySmallButton = new Button(	//
		Font{":)", 55, fontMap.at("comic serif"),0,0,90},
		square,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myDebugButton = new _debugbutton;


	//1.1 individial changes before grouping
	mySmallButton->scaleDimensions(50); myDebugButton->scaleDimensions(80);
	mySmallButton->isPrideful = true;		//	changes colour on click
	myStartButton->isEasilyScared = true;//hides on click
	myExitButton->isEasilyScared = true;
	myOptionsButton->isTogglable = true;	//	becomes togglablable (use button->isOn for the state)		

	myJankyText->textColour = SDL_COLOR_ROSE_TOY << SDL_White90;
	myJankySubText->textColour = SDL_COLOR_ROSE_TOY << SDL_White50; //	applying the transparency onto the colour
	myCreditingText->textColour = SDL_COLOR_ROSE_TOY << SDL_White25;

	//1.2 grouping (for mass attrbute changing, deleting and rendering)
	allButtons.emplace_back(myJankyText);	allButtons.emplace_back(myJankySubText); allButtons.emplace_back(myCreditingText); //	text
	allButtons.emplace_back(myStartButton);
	allButtons.emplace_back(myOptionsButton); 
	allButtons.emplace_back(myExitButton);	//	lowkey the layering (who's rendered on top)
	allButtons.emplace_back(mySmallButton);
	allButtons.emplace_back(myDebugButton);

	///	Step 2: Aesthetics

	for (auto* button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		button->onHoveringBackgroundColour = BUTTON_HOVERBACKGROUND; }

	myJankyText->offsetPosition(-300);	//	offsets the text up
	myJankySubText->setPositionRelativeTo(*myJankyText, 50, 375);
	myCreditingText->setPosition(20, 230);

	myStartButton->offsetPosition(-150);	//	offsets the start button 150 units vertically (up)
	myOptionsButton->offsetPosition(); //doesn't move the button (can take no parameters)
	myExitButton->offsetPosition(+150);	//	offsets the exit button 150 units vertically (down)

	//	cornering 
	mySmallButton->setPosition(SCREEN_HEIGHT - mySmallButton->getH(), SCREEN_WIDTH - mySmallButton->getW()); //	places the square button into the top corner
	myDebugButton->setPosition(0, SCREEN_WIDTH - myDebugButton->getW()); //	places the square button into the bottom corner

	///	step 3: Hitbox and OnClick

	audio->soundFinishedCallback = [&](int channel) { audio->stopSound(); };


	for (auto* button : allButtons) { button->generateHitbox(); } //	<-- DO AFTER RE-POSITIONING!!!!!!!!!!!!!! [this generates the Clickbox]
	//	what happens when each button is clicked?
	myStartButton->SetOnClick([&] {cc.consoleManager(update, "start pressed"); });
	myOptionsButton->SetOnClick([&] {cc.consoleManager(update, "options pressed"); });
	myExitButton->SetOnClick([&] {cc.consoleManager(update, "exit pressed"); });
	mySmallButton->SetOnClick([&] {cc.consoleManager(update, "small pressed"); });	
	myDebugButton->SetOnClick([&] {cc.consoleManager(update, "debug pressed | back from the dead!"); for(auto const button : allButtons) { button->isActive = true; }});




	return true;
}


void Scene1::OnDestroy() {
	for (auto* button : allButtons) { delete button; }
	
}


void Scene1::Update(const float deltaTime) {
	// Update player
	//game->getPlayer()->Update(deltaTime);

}


void Scene1::Render() {
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


	SDL_RenderPresent(renderer); }


void Scene1::HandleEvents(const SDL_Event& event) {
	PrettyPrinting::printMouseCoords(event);
	for (const auto button : allButtons) { button->HandleEvents(event); }



	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);

#pragma region debuggingKeys
	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN) {
		///	CONSOLE TESTING
		//	console messages display: how to call the method
		cc.consoleManager(error, "error: this is an error message");
		cc.consoleManager(warning, "warning: this is a warning message");
		cc.consoleManager(update, "update: this is an update message");
		cc.consoleManager(not_error, "this is not an error");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN) {
		audio->playSound("sound/blipblip.wav");
		using namespace ui;

		cc.consoleManager(update, "toggling all button visibility");
		for(auto button : allButtons) {
			bool state = button->isActive;
			button->isActive = !state; }

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {
		audio->stopSound();
	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN) {
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("dog")));
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("meow")));
	}


	if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN) {
		///	ENTITY MAP TESTING
		//	to insert into an entit map...
		eMap.insertEntity(string("rex"), string("is my dog"));
		eMap.insertEntity(string("deedee"), string("was my dog ;-;"));
		eMap.insertEntity(string("turnip"), string("is my cat"));
		eMap.insertEntity(string("adriel"), string("is adriel"));
		//	DELETING the test entity
		eMap.removeEntity(string("test"));
		//	printing...
		PrettyPrinting::printEM(eMap);
		//	to serialize that entity map...
		eMap.saveEntityMapToFile("SaveData/entitymap.txt");
	}
#pragma endregion
}
