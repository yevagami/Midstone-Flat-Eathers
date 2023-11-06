#include "GameManager.h"
#include "scene_list.h"


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


bool GameManager::OnCreate() {
	/// font
	if (TTF_Init() < 0) {
		std::cout << TTF_GetError() << std::endl;
		return false;
	}
	///


	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	// select scene for specific assignment
	currentScene = new SceneUI(windowPtr->GetSDL_Window(), this);


	// need to create Player before validating scene
	if (!ValidateCurrentScene()) {
		OnDestroy();
		return false;
	}

	std::cout << "Now loading: " << currentScene->name << std::endl;

	return true;
}


/// Here's the whole game loop
void GameManager::Run() {
	timer->Start();

	while (isRunning) {
		handleEvents();
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}


void GameManager::handleEvents() {
	SDL_Event event;

	// Let's add mouse movement and position
	// https://wiki.libsdl.org/SDL_GetMouseState

	SDL_PumpEvents(); // make sure we have the latest mouse state.

	//https://www.youtube.com/watch?v=SYrRMr4BaD4&list=PLM7LHX-clszBIGsrh7_3B2Pi74AhMpKhj&index=3

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { isRunning = false; }
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
				isRunning = false;	//	quits the game when ESCAPE is pressed
				break;
			case SDL_SCANCODE_Q:
				isRunning = false;	//	quits the game when Q is pressed
				break;
			case SDL_SCANCODE_DELETE:
				isRunning = false;	//	quits the game when DELETE is pressed
				break;
			case SDL_SCANCODE_0:
				system("cls"); //	clears the console when 0 is pressed
				break;
			case SDL_SCANCODE_1:
				LoadScene(1);
				break;
			case SDL_SCANCODE_2:
				LoadScene(2);
				break;
			case SDL_SCANCODE_3:
				LoadScene(3);
				break;
			case SDL_SCANCODE_4:
				LoadScene(4);
				break;

			default:
				break;
			}
		}
		currentScene->HandleEvents(event);
	}
}


GameManager::~GameManager() {}

void GameManager::OnDestroy() {
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;

	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
	}

	TTF_Quit();
}


// This might be unfamiliar
float GameManager::getSceneHeight() { return currentScene->getyAxis(); }

// This might be unfamiliar
float GameManager::getSceneWidth() { return currentScene->getxAxis(); }

// This might be unfamiliar
//Matrix4 GameManager::getProjectionMatrix() { return currentScene->getProjectionMatrix(); }

// This might be unfamiliar
SDL_Renderer* GameManager::getRenderer() {
	// [TODO] might be missing some SDL error checking
	SDL_Window* window = currentScene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	return renderer;
}


void GameManager::LoadScene(int i) {
	// cleanup of current scene before loading another one
	currentScene->OnDestroy();
	delete currentScene;

	//Checks if we killed everyone to switch the scene. Right now its going to change scenes automatically. We dont have a door yet
	if (ifDoorOpen == true) {
		i++; //this one will teleport us on the next scene
		i = (rand() % 4); //this one going to teleport us to a random scene from 0-3
	}
	
	switch (i) {
		playerMovedToTheNextLvl = true; //needed to spawn mobs AGAIN every time when we enter new room
	case 1:
		currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
		break;
	case 2:
		currentScene = new Scene2(windowPtr->GetSDL_Window(), this);
		break;
	case 3:
		currentScene = new Scene3(windowPtr->GetSDL_Window(), this);
		break;
	//case 4:
	//	//currentScene = new Scene4(windowPtr->GetSDL_Window(), this);
	//	break;
	case 5:
		currentScene = new SceneUI(windowPtr->GetSDL_Window(), this);
		break;
	default:
		currentScene = new Scene1(windowPtr->GetSDL_Window(), this);
		break;
	}

	// using ValidateCurrentScene() to safely run OnCreate
	if (!ValidateCurrentScene()) { isRunning = false; }
	std::cout << "Now loading: " << currentScene->name << std::endl;
}

void GameManager::PassTheLevel() {
	//Game loop win/loose the room (Diana)
	if (playerMovedToTheNextLvl) { //if we moved to the next room, reset the mob spawner
		mobsLeft = mobsToSpawnOnTheLevel; 
		if (mobsLeft == 0) {
			ifDoorOpen = true;
		}
	}
	
}

bool GameManager::ValidateCurrentScene() {
	if (currentScene == nullptr) { return false; }
	if (currentScene->OnCreate() == false) { return false; }
	return true;
}
