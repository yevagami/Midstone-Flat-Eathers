#include "Scene1.h"
#include <VMath.h>
#include <SDL_ttf.h>

#include "ConsistentConsole.h"
ConsistentConsole cc;
#include "PrettyPrinting.h"
PrettyPrinting print;
#include "FileManager.h"
FileManager file;
#include "SaveManager.h"
SaveManager save;
#include "EntityMap.h"
EntityMap eMap;

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

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	name = "scene1";

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);



}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	///	::TEMP MENU STUFF::
	//	1. Load a font
	TTF_Font* font;
	font = TTF_OpenFont("fonts/COMIC.TTF", 35);

	if (!font) {
		cc.consoleManager(error, "failed to load font | scene1 render");
	} else {

		//	2. set up a surface image with some text
		SDL_Surface* text;
		text = TTF_RenderText_Solid(font, "RAAAAAAA (centered)", ui::SDL_COLOR_BANANA_YELLOW);

		if (!text) {
			cc.consoleManager(error, "failed to render text");
		} else { 
			// 3. set up a texture for the surface
			SDL_Texture* text_ure;
			text_ure = SDL_CreateTextureFromSurface(renderer, text);


			//	Creating the button object (low parameter constructor edition)
			ui::Button myAsson(renderer);
			allButtons.push_back(&myAsson);
			ui::Button myBeuton(renderer);
			allButtons.push_back(&myBeuton);
			ui::Button myMegatron(renderer);
			allButtons.push_back(&myMegatron);
			ui::Button myNeutron(renderer);
			allButtons.push_back(&myNeutron);
			//	Creating a button object (many parameters constructor edition)
			ui::Button myProton(renderer, 3, 2, 0, 0,ui::SDL_COLOR_FOREST_GREEN, ui::SDL_COLOR_BLACK);
			allButtons.push_back(&myProton);

			//	mass attribute changing
			for (ui::Button* button : allButtons) {
				button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
				button->setDimensions(75, 425);	//	default is 2 : 4
				button->SetOnClick([] { cc.consoleManager(update, "button clicked"); });
			}
			//	single attribute changing
			myAsson.offsetPosition(250);			myAsson.backgroundColour = ui::SDL_COLOR_POOPSTAIN;
			myMegatron.offsetPosition(125);		myMegatron.backgroundColour = ui::SDL_COLOR_DARK_GREEN;
			myProton.offsetPosition(0);				//	colour set in the constructor ;), we could change it here but we dont need to
			myNeutron.offsetPosition(-125);		myNeutron.backgroundColour = ui::SDL_COLOR_STARRY_NIGHT;
			myBeuton.offsetPosition(-250);		myBeuton.backgroundColour = ui::SDL_COLOR_MARINE_BLUE;
	
			//	rendering buttons (not ideal cuz each button has a seperate font and text texture)
			for (ui::Button* button : allButtons) {
				button->Render(text_ure, font);
			}

			//	freeing stuff up
			SDL_DestroyTexture(text_ure);

		}

		SDL_FreeSurface(text);

	}

	// render the player
	game->RenderPlayer(0.1f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	/*key.HandleEvents(event);*/

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);



#pragma region debuggingKeys
	//	debug keys (for debugging)
	if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN) {
		///	SAVE SYSTEM TESTING
		if (file.fileCheck(save.getCurrentSaveFileDirectory())) {

			cc.consoleManager(update, "current save file directory created!");
			save.addValueToCurrentSaveFile("animal", "dog1");	//	unique variables required or they wont store
			save.addValueToCurrentSaveFile("animal", "dog2");	//	*only dog1 stores*
			save.addValueToCurrentSaveFile("animal", "dog3");	//	

			save.addValueToCurrentSaveFile("felines", "cat, 4 legs, 100 whiskers, 3200 toes, your social insurance number");
			save.addValueToCurrentSaveFile("canines", "dog, 3 legs, rip last leg, this is soo sad, im gonna const bool myself-");

		}
		else {
			cc.consoleManager(error, "cannot create save file for some reason");
		}
	}


	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN) {
		///	CONSOLE TESTING
			//	console messages display: how to call the method
		cc.consoleManager(error, "this is an error message");
		cc.consoleManager(warning, "this is a warning message");
		cc.consoleManager(update, "this is an update message");
		cc.consoleManager(safe, "this is a safe message");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN) {

		///	doesnt work rn >:(
		save.clearBothSaves();

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {
		eMap.insertEntity(string("test"), string("meowmeowmeow"));

	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN) {
		print.printVS(eMap.findEntitiesByData(string("dog")));
		print.printVS(eMap.findEntitiesByData(string("meow")));
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
		print.printEM(eMap);
		//	to serialize that entity map...
		eMap.saveEntityMapToFile("SaveData/entitymap.txt");


	}
#pragma endregion


}
