#include "GameManager.h"
#include "scene_list.h"

#pragma region GLOBAL NAMESPACE
void InitializeSoundEffects() {
	///	Initialize sound effects here and link them to a label. Then call them from the label in-scene.
	//		music
	sound.loadSound("theme", "sound/19. Select Position (Wii Sports).wav");
	//		sfx
	sound.loadSound("wong", "sound/wooooooooooooong.wav");
	sound.loadSound("flame", "sound/flame.wav");
	sound.loadSound("space boing", "sound/space boing.wav");
	sound.loadSound("big powerup", "sound/big powerup.wav");
	sound.loadSound("blipblip", "sound/blipblip.wav");
	sound.loadSound("bip", "sound/bip.wav");
	sound.loadSound("ting", "sound/ting.wav");
	sound.loadSound("boomp", "sound/boomp.wav");
	sound.loadSound("dying printer", "sound/dying printer.wav");
	//		test
	sound.loadSound("my bike", "sound/wait till you see me on my bike.wav");
	sound.loadSound("oops", "sound/oops.wav");
	sound.loadSound("gyat", "sound/gyat.wav");
	sound.loadSound("my move", "sound/once i make my move.wav");

	///	SOUND EFFECTS GROUP HERE
	sound.createSoundGroup(type::sfx);	//	creating a sound group for sfx

	sound.addToSoundGroup("blipblip", type::sfx);
	sound.addToSoundGroup("bip", type::sfx);
	sound.addToSoundGroup("ting", type::sfx);
	sound.addToSoundGroup("flame", type::sfx);
	sound.addToSoundGroup("boomp", type::sfx);

	sound.setGroupVolume(type::sfx, settings::SoundEffectVolume); 	//	dont touch this 

	///	MUSIC GROUPS HERE
	sound.createSoundGroup(type::music);	//	creating a sound group for music

	sound.addToSoundGroup("big powerup", type::music);
	sound.addToSoundGroup("wong", type::music);
	sound.addToSoundGroup("dying printer", type::music);
	sound.addToSoundGroup("my move", type::music);

	sound.setGroupVolume(type::music, settings::MusicVolume);	//	dont touch this 

	sound.createSoundGroup(type::test);
	sound.addToSoundGroup("oops", type::test);
	sound.addToSoundGroup("my bike", type::test);
	sound.addToSoundGroup("gyat", type::test);
}
#pragma endregion


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
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
	InitializeSoundEffects();



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

	//StartFadeOutTransition(2000); // 2000 milliseconds (2 seconds) fade out animation


	while (isRunning) {
		timer->UpdateFrameTicks();
		const float deltaTime = timer->GetDeltaTime();


		if (fadeTransition) {								//	if a fadeTransition unique ptr exists
			if (!fadeTransition->isComplete()) {	//	when the fadeTransition is in progress

				currentScene->Update(deltaTime);
				currentScene->Render();

				fadeTransition->Draw();				//	draws the fade rectangle based on the alpha
				cc.colour(green); cout << "fade time remaining is " << fadeTransition->GetRemainingTime() << "ms"; cc.colour(clear, newline);
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

		if (event.type == SDL_QUIT) { isRunning = false; }
		else if (event.type == SDL_KEYDOWN) {
			//	keyboard event checking
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
				isPaused = !isPaused;
				isRunning = false; // for now, eventually this'll enable/disable a menuScene 
				break;
			case SDL_SCANCODE_Q:
				isRunning = false;	//	quits the game when Q is pressed
				break;
			case SDL_SCANCODE_I:
				//	testing
				StartFadeInTransition(2000);
				break;
			case SDL_SCANCODE_O:
				StartFadeOutTransition(2000);
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

		//	check what events are occuring in the currentScene
		currentScene->HandleEvents(event);
	}
}


GameManager::~GameManager() {}

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
	if (!ValidateCurrentScene()) { isRunning = false; }
	std::cout << "Now loading: " << currentScene->name << std::endl;
}


bool GameManager::ValidateCurrentScene() {
	if (currentScene == nullptr) { return false; }
	if (currentScene->OnCreate() == false) { return false; }
	return true;
}
