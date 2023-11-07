#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
//#include <SDL_ttf.h>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
//#include <iostream>

#include "Audio.h"
#include "ConsistentConsole.h"
#include "PrettyPrinting.h"




	inline Sound sound;
	void InitializeSoundEffects();

namespace settings {
	inline float MasterVolume;
	inline float MaxVolume = 100.0f;

	inline float SoundEffectVolume;
	inline float MusicVolume;

	inline void SetVolume(float newVolume_) {
		sound.setVolume(newVolume_);
	}
}

	inline ConsistentConsole cc(true);
	inline PrettyPrinting pp;




// My display is 1920 x 1080 but the following seems to work best to fill the screen.
//const int SCREEN_WIDTH = 1540;
//const int SCREEN_HEIGHT = 860;


//	Sound goes in here, the GameManager


// Use 1000x600 for less than full screen
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;


class GameManager {
private:
	/// These are called "forward declarations" The idea is that a pointer is 
	/// really just an unsigned int, so to create a pointer to it you really only
	/// need to tell the compiler that there is a class called Window and I need
	/// a pointer to it, thus the "class Window*" means trust me, there is a class 
	/// called Window, I just need a pointer to it.

	/// If that was too much for your brain, just #include "Window.h" and declare
	/// Window *ptr and don't use the word "class"  This is a second semester C++
	/// topic anyway
	class Window *windowPtr;
	class Timer *timer;
	bool isRunning;
	class Scene *currentScene;

	//For the game loop Diana
	bool ifDoorOpen = false;
	int mobsToSpawnOnTheLevel = 10;
	int mobsLeft;
	bool playerMovedToTheNextLvl = true;


	//	sound stuff (test - Michael)




public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();

	// These might be unfamiliar
	float getSceneHeight();
	float getSceneWidth();
	//Matrix4 getProjectionMatrix();
	SDL_Renderer* getRenderer();

	void Run();
	void handleEvents();
	void LoadScene( int i );
	void PassTheLevel(); //new
    bool ValidateCurrentScene();


};
#endif


