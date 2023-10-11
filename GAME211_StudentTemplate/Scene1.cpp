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
//#include <VMath.h>
//#include <SDL_ttf.h>


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
	using namespace ui;

	ui::Button* myDefaultButton = new ui::Button;

	auto* myCustomButton = new Button(	//	_debugbutton
		Font{"cool words", 90, fontMap.at("gothic"),0,0,-45 }, 
		SDL_Square, 
		SDL_COLOR_POOPSTAIN, SDL_COLOR_WARM_STREAM);

	myDefaultButton->text = "my default text";
	myDefaultButton->setDimensions(SDL_Rectangle);
	allButtons.emplace_back(myDefaultButton);
	allButtons.emplace_back(myCustomButton);

	for (auto* button : allButtons) {
		button->scaleDimensions(120);
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	myDefaultButton->offsetPosition(200);
	myCustomButton->offsetPosition(-100);

	return true;
}

void Scene1::OnDestroy() {
	//for (auto button : allButtons) { delete button; }
	
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


	SDL_RenderPresent(renderer);
}

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
