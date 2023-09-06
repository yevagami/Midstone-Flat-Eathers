#include "GameManager.h"
#include "scene_list.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}

bool GameManager::OnCreate(int width_, int height_, const char* window_name) {
	// initiate a new window and timer objects
	windowPtr = new Window(width_, height_, window_name);
	timer = new Timer();

	// If the window or time objects are not created or the window is not intialized  
	if (!windowPtr || !timer  || !windowPtr->OnCreate()) {
		OnDestroy();
		return false;
	}

	// Intilize the scene.
	currentScene = new scene_test(windowPtr->GetSDL_Window());

	// If the scene object is not created or the scene is not intialized  
	if (!currentScene || !currentScene->OnCreate()) {
		OnDestroy();
		return false;
	}

	return true;
}

void GameManager::Run() {

	// Event handler
	SDL_Event e;

	// Start the timer
	timer->Start();
	
	// While the application is running
	while (isRunning) {
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User requests quit (by clicking x at the top)
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
			}

			else {
				currentScene->HandleEvents(e);
			}
		}

		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); //60 frames per sec
	}


}

GameManager::~GameManager() {
}

void GameManager::OnDestroy() {
	// Release all the Scene's assets
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
	}

	if (windowPtr) {
		windowPtr->OnDestroy();
		delete windowPtr;
	}

	if (timer) delete timer;
}