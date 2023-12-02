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
	inline Sound musicSound;
	inline Sound sfxSound;


#pragma region settings
	namespace settings {
		inline float MaxVolume = 1.0f;
		inline float MasterVolume;
		inline float DefaultMasterVolume = 1.0f;

		inline float SoundEffectVolume;
		inline float DefaultSoundEffectVolume = 1.0f;

		inline float MusicVolume;
		inline float DefaultMusicVolume = 1.0f;

		inline int FPS;

		inline void SetMusicVolume(const float newMusicVolume_) {
			if (newMusicVolume_ < -0.1f || newMusicVolume_ > 1.0f) { return; }

			MusicVolume = std::min(newMusicVolume_, MasterVolume);
			musicSound.setVolume(MusicVolume);
		}

		inline void SetSFXVolume(const float newSFXVolume_) {
			if (newSFXVolume_ < -0.1f || newSFXVolume_ > 1.0f) { return; }

			SoundEffectVolume = std::min(newSFXVolume_, MasterVolume);
			sfxSound.setVolume(SoundEffectVolume);
		}

		inline void SetMasterVolume(const float newMaterVolume_) {
			if (newMaterVolume_ < -0.1f || newMaterVolume_ > 1.0f) { return; }

			//	compare the newMaster to the MaxVolume and take the lowest
			MasterVolume = std::min(newMaterVolume_, MaxVolume);

			//update the other volumes cuz the master changed
			SetMusicVolume(MusicVolume);
			SetSFXVolume(SoundEffectVolume);
		}

	}
#pragma endregion

	inline void InitSoundEffects() {
		sfxSound.loadSound("my bike", "sound/wait till you see me on my bike.wav");


		sfxSound.setVolume(settings::SoundEffectVolume);	//	dont touch this 
	}
	inline void InitMusic() {
		musicSound.loadSound("theme", "sound/19. Select Position (Wii Sports).wav");


		musicSound.setVolume(settings::MusicVolume);	//	dont touch this 
	}
	inline ConsistentConsole cc(true, "GameManager.h");
	inline PrettyPrinting pp(pink, purple, cyan);

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
	static void setDefaultSettings() {
		settings::FPS = 60;
		settings::MaxVolume = 1.0f;
		settings::MasterVolume = settings::DefaultMasterVolume;;
		settings::MusicVolume = settings::DefaultMusicVolume;
		settings::SoundEffectVolume = settings::DefaultSoundEffectVolume;
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
