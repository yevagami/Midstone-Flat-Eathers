#include "Scene1.h"

#include "PrettyPrinting.h"

#include "ConsistentConsole.h"
//a global var. My problem was that i defined it in the Scene 3 again, that made a linking error.
//IMPORTANT!!!
ConsistentConsole cc; //not member of scene1 class. Define somewhere else 
//#include "FileManager.h"
//FileManager file;
#include "SaveManager.h"
SaveManager save;//not member of scene1 class
#include "EntityMap.h"
EntityMap eMap;//not member of scene1 class


//#include <VMath.h>
//#include <SDL_ttf.h>

//#include "KeybindHandler.h"
//keybinds::keys key;






// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {

	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene1::~Scene1() = default;

bool Scene1::OnCreate()//??
{
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

	auto* myButton  = new ui::Button(renderer, "my butt(on)", SDL_Testangle, ui::SDL_COLOR_WASHING_MACHINE, 
		ui::Font{45, ui::fontMap.at("wingdings")}, SDL_COLOR_SOUL_CAMPFIRE);

	allButtons.emplace_back(myButton);

	for (auto* button : allButtons) {
		button->scaleDimensions(2);
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		button->generateHitbox();
		button->SetOnClick([&]() {
			cc.consoleManager(not_error, "the click of 87");
			});
	}

	return true;
}

void Scene1::OnDestroy() {
	for (auto button : allButtons) {
		delete button;
	}


}

void Scene1::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);



}

void Scene1::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


	//	render the buttons
	for (auto* button : allButtons) {
		button->Render(renderer);
	}
	//	clear the allButtons vector


	// render the player
	game->RenderPlayer(0.1f);


	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event) {
	PrettyPrinting::printMouseCoords(event);

	for (const auto button : allButtons) {
		button->HandleEvents(event);
	}


	// send events to player as needed
	game->getPlayer()->HandleEvents(event);


#pragma region debuggingKeys
	//	debug keys (for debugging)
	//if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN)
	{
		///	SAVE SYSTEM TESTING
		/*if (file.fileCheck(save.getCurrentSaveFileDirectory()))
		{
			cc.consoleManager(update, "current save file directory created!");
			save.addValueToCurrentSaveFile(
				"animal", "dog1"); //	unique variables required or they wont store
			save.addValueToCurrentSaveFile(
				"animal", "dog2"); //	*only dog1 stores*
			save.addValueToCurrentSaveFile(
				"animal", "dog3"); //	
			save.addValueToCurrentSaveFile(
				"felines", "cat, 4 legs, 100 whiskers, 3200 toes, your social insurance number");
			save.addValueToCurrentSaveFile(
				"canines", "dog, 3 legs, rip last leg, this is soo sad, im gonna const bool myself-");
		}
		else
		{
			cc.consoleManager(error, "cannot create save file for some reason");
		}*/
	}


	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN)
	{
		///	CONSOLE TESTING
		//	console messages display: how to call the method
		cc.consoleManager(error, "error: this is an error message");
		cc.consoleManager(warning, "warning: this is a warning message");
		cc.consoleManager(update, "update: this is an update message");
		cc.consoleManager(not_error, "this is not an error");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN)
	{
		///	doesnt work rn >:(
		save.clearBothSaves();

		

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN)
	{
		eMap.insertEntity(string("test"), string("meowmeowmeow"));
	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN)
	{
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("dog")));
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("meow")));
	}


	if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN)
	{
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
