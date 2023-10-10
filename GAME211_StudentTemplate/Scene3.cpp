#include "Scene3.h"
#include <VMath.h>
#include <SDL_ttf.h>

#include "PrettyPrinting.h"
#include "ConsistentConsole.h"
//ConsistentConsole cc;
#include "FileManager.h"
//FileManager file;
#include "SaveManager.h"
//SaveManager save;
#include "EntityMap.h"
//EntityMap eMap;

//#include "KeybindHandler.h"
//keybinds::keys key;






// See notes about this constructor in Scene1.h.
Scene3::Scene3(SDL_Window* sdlWindow_, GameManager* game_) {

	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene3::~Scene3() = default;

bool Scene3::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "scene3";



	return true;
}

void Scene3::OnDestroy() {}

void Scene3::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);

	//for (ui::Button* button : allButtons) {
	//	button->Update(deltaTime);
	//}

}

void Scene3::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	using namespace ui;

	//	Creating the button objects 
	ui::Button myButton(renderer, "my button", ui::SDL_Testangle, ui::SDL_COLOR_WASHING_MACHINE);
	ui::Button myAsson(renderer, "ass", ui::SDL_Testangle, ui::SDL_COLOR_TOOTHBRUSH,
		ui::Font({ 55, ui::fontMap.at("heebo") }));
	ui::Button myBeuton(renderer, "beu", ui::SDL_Testangle, ui::SDL_COLOR_REINHARDT); //, ui::fontMap.at("open sans")
	ui::Button myJimmy(renderer, "jilly", ui::SDL_Testangle, ui::SDL_COLOR_CASSIDY); //ui::fontMap.at("roboto")
	ui::Button myNeutron(renderer, "niltril", ui::SDL_Testangle, ui::SDL_COLOR_CRIMSON_RED);
	ui::Button myProton(renderer, "BOO!!!", ui::SDL_Testangle, ui::SDL_COLOR_SCARLET_RED,
		ui::Font({ 100, ui::fontMap.at("gothic") }));

	allButtons.push_back(&myButton);
	allButtons.push_back(&myAsson);
	allButtons.push_back(&myBeuton);
	allButtons.push_back(&myJimmy);
	allButtons.push_back(&myNeutron);
	allButtons.push_back(&myProton);

	//	mass attribute changing
	for (ui::Button* button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		//button->SetOnClick([] { cc.consoleManager(update, "button clicked"); });
	}

	//	single attribute changing
	myButton.offsetPosition(-250, -250);

	myAsson.offsetPosition(250, -250);
	myJimmy.offsetPosition(125, -125);
	myProton.offsetPosition(0);
	myNeutron.offsetPosition(-125, 125);
	myBeuton.offsetPosition(-250, 250);


	//	render the buttons
	for (ui::Button* button : allButtons) {
		if (button->Render()) { button->setPosition(); }
	}
	//	clear the allButtons vector
	allButtons.clear();


	// render the player
	game->RenderPlayer(0.1f);

	SDL_RenderPresent(renderer);
}

void Scene3::HandleEvents(const SDL_Event& event)
{
	/*key.HandleEvents(event);*/

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);


#pragma region debuggingKeys
	//	debug keys (for debugging)
	if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN)
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
		//cc.consoleManager(error, "error: this is an error message");
		//cc.consoleManager(warning, "warning: this is a warning message");
		//cc.consoleManager(update, "update: this is an update message");
		//cc.consoleManager(not_error, "this is not an error");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN)
	{
		///	doesnt work rn >:(
		//save.clearBothSaves();
	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN)
	{
		//eMap.insertEntity(string("test"), string("meowmeowmeow"));
	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN)
	{
		//PrettyPrinting::printVS(eMap.findEntitiesByData(string("dog")));
		//PrettyPrinting::printVS(eMap.findEntitiesByData(string("meow")));
	}


	if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN)
	{
		///	ENTITY MAP TESTING
		//	to insert into an entit map...
		/*eMap.insertEntity(string("rex"), string("is my dog"));
		eMap.insertEntity(string("deedee"), string("was my dog ;-;"));
		eMap.insertEntity(string("turnip"), string("is my cat"));
		eMap.insertEntity(string("adriel"), string("is adriel"));*/
		//	DELETING the test entity
		//eMap.removeEntity(string("test"));
		//	printing...
		//PrettyPrinting::printEM(eMap);
		//	to serialize that entity map...
		//eMap.saveEntityMapToFile("SaveData/entitymap.txt");
	}
#pragma endregion
}
