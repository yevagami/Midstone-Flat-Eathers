#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <functional>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"

#include "Audio.h"
#include "ConsistentConsole.h"
#include "PrettyPrinting.h"
#include "FadeTransition.h"
#include "FileManager.h"


//	global classes
	inline Sound sound; void InitializeSoundEffects();
	inline ConsistentConsole cc(true, "GameManager.h");
	inline PrettyPrinting pp(pink, purple, cyan);

	#pragma region settings
namespace settings {
	inline float MaxVolume = 1.0f;
	inline float MasterVolume;

	inline float SoundEffectVolume;
	inline float MusicVolume;

	inline int FPS;

	inline void SetFPS(const int newFPS_) {
		if (newFPS_ != 30 || newFPS_ != 60) {
			return;
		}
		settings::FPS = newFPS_;
	}
		
	inline void SetMusicVolume(const float newMusicVolume_) {
		if (newMusicVolume_ < 0.0f || newMusicVolume_ > 1.0f) { return; }

		MusicVolume = newMusicVolume_;
		sound.setGroupVolume(type::music, MusicVolume * MasterVolume);
	}

	inline void SetSFXVolume(const float newSFXVolume_) {
		if (newSFXVolume_ < 0.0f || newSFXVolume_ > 1.0f) { return; }

		SoundEffectVolume = newSFXVolume_;
		sound.setGroupVolume(type::sfx, SoundEffectVolume * MasterVolume);
	}

	inline void SetMasterVolume(const float newMaterVolume_) {
		if (newMaterVolume_ < 0.0f || newMaterVolume_ > 1.0f) { return; }

		//	compare the newMaster to the MaxVolume and take the lowest
		MasterVolume = std::min(newMaterVolume_, MaxVolume);
		sound.setVolume(MasterVolume);

		//update the other volumes cuz the master changed
		SetMusicVolume(MusicVolume);
		SetSFXVolume(SoundEffectVolume);
	}

}
#pragma endregion

// My display is 1920 x 1080 but the following seems to work best to fill the screen.
//const int SCREEN_WIDTH = 1540;
//const int SCREEN_HEIGHT = 860;


// Use 1000x600 for less than full screen
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

//	i moved this here so i can access it from deeper
inline bool isRunning;

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
	class Scene *currentScene;
	Scene *menuScene;

	//	michael's playground ahahhahahaha
	std::unique_ptr<FadeTransition> fadeTransition; // frick manual memory management, we quirky pointer
	bool isPaused;

	//	settings default values
	void setDefaultSettings() {
		settings::FPS = 60;
		settings::MasterVolume = 1.0f;
		settings::MaxVolume = 1.0f;
		settings::MusicVolume = 0.5f;
		settings::SoundEffectVolume = 0.75f;
	}

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
	void HandleEvents();
	void LoadScene( int i_ );
    bool ValidateCurrentScene();


	//	Fade IN transition (fade in to black) (yes its confusing)
	void StartFadeInTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr) {
		cc.log(debug, "fade in animation called");
		//	create a fadeTransition using the current window's renderer, current screen height, current screen width, the fade time, and fade type
		fadeTransition = std::make_unique<FadeTransition>(getRenderer(), settings::FPS, getSceneHeight(), getSceneWidth(), fadeTime_, true);
		fadeTransition->SetStartTime();

		if (callback_) {
			fadeTransition->SetCallback(callback_);
		}
	}

	//	Fade OUT transition (fade out from black)
	void StartFadeOutTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr) {
		cc.log(debug, "fade out animation called");
		//	create a fadeTransition using the current window's renderer, current screen height, current screen width, the fade time, and fade type
		fadeTransition = std::make_unique<FadeTransition>(getRenderer(), settings::FPS, getSceneHeight(), getSceneWidth(), fadeTime_, false);
		fadeTransition->SetStartTime();

		if (callback_) {
			fadeTransition->SetCallback(callback_);
		}
	}


};
#endif
