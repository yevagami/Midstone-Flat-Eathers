#include "GameManager.h"
#include "scene_list.h"


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	settings::isRunning = true;
	isPaused = false;
	currentScene = nullptr;
	menuScene = nullptr;

	setDefaultSettings();
}


bool GameManager::OnCreate() {
	///	font
	if (TTF_Init() < 0) {
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	///	sound
	LoadMusic();
	LoadSoundEffects();


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

	//	load the menu scene on top of the current scene
	menuScene = new SceneUI(windowPtr->GetSDL_Window(), this);
	// select scene for specific assignment
	currentScene = new PlayScene(windowPtr->GetSDL_Window(), this);


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


	while (settings::isRunning) {
		timer->UpdateFrameTicks();
		const float deltaTime = timer->GetDeltaTime();

		if (fadeTransition) {								//	if a fadeTransition unique_ptr exists
			if (!fadeTransition->isComplete()) {	//	when the fadeTransition is in progress
				///	keep the present scene visible
				//currentScene->Render();
				///	render the fade higher in priority
				fadeTransition->Draw();				//	draws the fade rectangle based on the alpha

			} else {												// when the fade transition is done...
				fadeTransition.reset();					//	reset the unique pointer (make it nullptr)
			}
		}else {
			//	if theres no fadeTransition in progress, update and render the scene as usual
			currentScene->Update(deltaTime);
			currentScene->Render();
		}
		HandleEvents();
		
		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(settings::FPS)); ///60 frames per sec
	}
}


void GameManager::HandleEvents() {
	SDL_Event event;

	// Let's add mouse movement and position
	// https://wiki.libsdl.org/SDL_GetMouseState

	SDL_PumpEvents(); // make sure we have the latest mouse state.

	//https://www.youtube.com/watch?v=SYrRMr4BaD4&list=PLM7LHX-clszBIGsrh7_3B2Pi74AhMpKhj&index=3

	while (SDL_PollEvent(&event)) {

		//	The events that get handled first. Anything occuring in a handleEvents deeper than this has lower priority
		//	don't accidentally cause conflicts

		if (event.type == SDL_QUIT) { quitPls(); }
		else if (event.type == SDL_KEYDOWN) {
			//	keyboard event checking
			switch (event.key.keysym.scancode) {  // NOLINT(clang-diagnostic-switch-enum)
			case SDL_SCANCODE_UNKNOWN:
				cc.log(error, "wtf did you press???");
				break;
			case SDL_SCANCODE_ESCAPE:
				//isPaused = !isPaused;
				StartFadeInTransition(1000, [this]() { quitPls(); });
				break;
			case SDL_SCANCODE_Q:
				StartFadeInTransition(1000, [this]() { quitPls();	 });
				break;
			case SDL_SCANCODE_END:
				cc.log(update, "SILENCE!!!");
				musicSound.stopAllSounds();
				sfxSound.stopAllSounds();
				break;
			case SDL_SCANCODE_I:
				//	testing
				StartFadeInTransition(500);
				break;
			case SDL_SCANCODE_O:
				//musicSound.playSound("ominous music");
				sfxSound.playSound("slash");
				break;
			case SDL_SCANCODE_0:
				system("cls");  // NOLINT(concurrency-mt-unsafe)
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

		//	check what events are occuring in the currentScene
		currentScene->HandleEvents(event);
	}
}


GameManager::~GameManager() = default;

void GameManager::OnDestroy() {
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;

	//	not needed cuz its unique and self-manages (allegedly)
	//if (fadeTransition) delete fadeTransition;

	if (menuScene) {
		menuScene->OnDestroy();
		delete menuScene;
	}

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
	cc.log(not_error, "renderer requested (GameManager.getRenderer();)");
	// [TODO] might be missing some SDL error checking
	SDL_Window* window = currentScene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	return renderer;
}


void GameManager::LoadScene(const int i_) {
	// cleanup of current scene before loading another one
	currentScene->OnDestroy();
	delete currentScene;

	switch (i_) {
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
	if (!ValidateCurrentScene()) { settings::isRunning = false; }
	std::cout << "Now loading: " << currentScene->name << std::endl;
}


bool GameManager::ValidateCurrentScene() {
	if (currentScene == nullptr) { return false; }
	if (currentScene->OnCreate() == false) { return false; }
	return true;
}

void GameManager::StartFadeInTransition(const Uint64 fadeTime_, const std::function<void()>& callback_) {
	cc.log(debug, "fade in animation called");
	//	create a fadeTransition using the current window's renderer, current screen height, current screen width, the fade time, and fade type
	fadeTransition = std::make_unique<FadeTransition>(getRenderer(), settings::FPS, getSceneHeight(), getSceneWidth(), fadeTime_, true, callback_);
	fadeTransition->SetStartTime();


}

//void GameManager::StartFadeOutTransition(const Uint64 fadeTime_, const std::function<void()>& callback_) {
//	cc.log(debug, "fade out animation called");
//	//	create a fadeTransition using the current window's renderer, current screen height, current screen width, the fade time, and fade type
//	fadeTransition = std::make_unique<FadeTransition>(getRenderer(), settings::FPS, getSceneHeight(), getSceneWidth(), fadeTime_, false, callback_);
//	fadeTransition->SetStartTime();
//}
