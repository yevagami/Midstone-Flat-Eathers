#include "Scene1.h"
#include <VMath.h>

#include "ConsistentConsole.h"
ConsistentConsole cc;
#include "FileManager.h"
FileManager file;
#include "LogManager.h"
#include "SaveManager.h"
SaveManager save;


// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene1::~Scene1(){}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);

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

	// render the player
	game->RenderPlayer(0.1f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{







	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

#pragma region debuggingKeys
	//	debug keys (for debugging)
	if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN) {
		if (file.fileCheck(save.getCurrentSaveFileDirectory())) {
				
			cc.consoleManager(update, "current save file directory created!");
			save.addValueToCurrentSaveFile("animal", "dog");

		} else {
			cc.consoleManager(error, "cannot create save file for some reason");
		}
	}


	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN) {
			//	console messages display: how to call the method
		cc.consoleManager(error, "this is an error message");
		cc.consoleManager(warning, "this is a warning message");
		cc.consoleManager(update, "this is an update message");
		cc.consoleManager(safe, "this is a safe message");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN) {

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {

	}


	if (event.key.keysym.sym == SDLK_p && event.type == SDL_KEYDOWN) {

	}
#pragma endregion


}
