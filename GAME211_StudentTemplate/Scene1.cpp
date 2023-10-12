#include "Scene1.h"
#include "PrettyPrinting.h"
#include "ConsistentConsole.h"
//a global var. My problem was that i defined it in the Scene 3 again, that made a linking error.
//IMPORTANT!!!
ConsistentConsole cc; //not member of scene1 class. Define somewhere else 
//#include "FileManager.h"
//FileManager file;
#include "SaveManager.h"
SaveManager save; //not member of scene1 class
#include "EntityMap.h"
EntityMap eMap; //not member of scene1 class

#include "GameObjects.h"



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

	///	Step 1: Create the Buttons with Default Values

	auto* myJankyText = new Button(Font{"ur amazing<3", 100});
	auto* myJankySubText = new Button(Font{"with rizz", 25, fontMap.at("comic sans"),0,0,-45.0});

	auto* myStartButton = new Button(	//	_debugbutton
		Font{"start button", 50, fontMap.at("ransom")}, 
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myOptionsButton = new Button(	//	
		Font{ "options button", 50, fontMap.at("lobster") },
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myExitButton = new Button(	//	
		Font{ "exit button", 50, fontMap.at("verdana") },
		rectangle,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* mySmallButton = new Button(	//
		Font{":)", 55, fontMap.at("ransom"),0,0,90},
		square,
		BUTTON_BACKGROUND, BUTTON_TEXT);

	auto* myDebugButton = new _debugbutton;

	//1.1 aesthetics before grouping
	mySmallButton->scaleDimensions(50); myDebugButton->scaleDimensions(80); myStartButton->backgroundColour = SDL_COLOR_BAD_DRAGON;
	myJankyText->textColour = SDL_COLOR_ROSE_TOY;
	myJankySubText->textColour = SDL_COLOR_ROSE_TOY % SDL_White50;
	//1.2 grouping
	allButtons.emplace_back(myJankyText);	allButtons.emplace_back(myJankySubText);
	allButtons.emplace_back(myStartButton);
	allButtons.emplace_back(myOptionsButton); //	lowkey the layering (who's on top)
	allButtons.emplace_back(myExitButton);
	allButtons.emplace_back(mySmallButton);
	allButtons.emplace_back(myDebugButton);

	///	Step 2: Aesthetics

	for (auto* button : allButtons) { button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT); }
	myJankyText->offsetPosition(-300);	//	offsets the text up
	myJankySubText->setPositionRelativeTo(*myJankyText, 50, 300);

	myStartButton->offsetPosition(-150);	//	offsets the start button 150 units vertically (up)
	myOptionsButton->offsetPosition(); //	not needed, purely for visuals
	myExitButton->offsetPosition(+150);	//	offsets the exit button 150 units vertically (down)

	mySmallButton->setPosition(SCREEN_HEIGHT - mySmallButton->getH(), SCREEN_WIDTH - mySmallButton->getW()); //	places the square button into the top corner
	myDebugButton->setPosition(0 /*+ myDebugButton->getH()*/, SCREEN_WIDTH - myDebugButton->getW()); //	places the square button into the bottom corner

	///	step 3: Hitbox and OnClick

	for (auto* button : allButtons) { button->generateHitbox(); } //	<-- DO AFTER RE-POSITIONING!!!!!!!!!!!!!! [this generates the Clickbox]

	myStartButton->SetOnClick([&] {cc.consoleManager(update, "start pressed"); });
	myOptionsButton->SetOnClick([&] {cc.consoleManager(update, "options pressed"); });
	myExitButton->SetOnClick([&] {cc.consoleManager(update, "exit pressed"); });
	mySmallButton->SetOnClick([&] {cc.consoleManager(update, "small pressed"); });

	return true;
}


void Scene1::OnDestroy() {
	for (auto* button : allButtons) { delete button; }
	
}


void Scene1::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);

}


void Scene1::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


	
	//	render the buttons
	for (auto* button : allButtons) { button->Render(renderer); }
	

	// render the player
	game->RenderPlayer(0.1f);


	SDL_RenderPresent(renderer); }


void Scene1::HandleEvents(const SDL_Event& event) {
	PrettyPrinting::printMouseCoords(event);
	for (const auto button : allButtons) { button->HandleEvents(event); }



	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

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
		using namespace ui;


	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {
		eMap.insertEntity(string("test"), string("meowmeowmeow"));
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
