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
	inline ConsistentConsole cc(true, "GameManager.h");
	inline PrettyPrinting pp(pink, purple, cyan);


#pragma region settings
	namespace settings {
		inline float MaxVolume = 1.0f;
		inline float MasterVolume;
		inline float DefaultMasterVolume = 0.5f;

		inline float SoundEffectVolume;
		inline float DefaultSoundEffectVolume = 0.5f;

		inline float MusicVolume;
		inline float DefaultMusicVolume = 0.5f;

		inline int FPS;

		inline bool isRunning;

		inline void SetMusicVolume(const float newMusicVolume_) {
			if (newMusicVolume_ < -0.0f || newMusicVolume_ > 1.0f) { return; }


			MusicVolume = std::min(newMusicVolume_, MasterVolume);
			musicSound.setVolume(MusicVolume);
		}

		inline void SetSFXVolume(const float newSFXVolume_) {
			if (newSFXVolume_ < -0.0f || newSFXVolume_ > 1.0f) { return; }


			SoundEffectVolume = std::min(newSFXVolume_, MasterVolume);
			sfxSound.setVolume(SoundEffectVolume);
		}

		inline void SetMasterVolume(const float newMaterVolume_) {
			if (newMaterVolume_ < -0.0f || newMaterVolume_ > 1.0f) { return; }

			//	compare the newMaster to the MaxVolume and take the lowest
			MasterVolume = std::min(newMaterVolume_, MaxVolume);

			SetMusicVolume(MusicVolume);
			SetSFXVolume(SoundEffectVolume);
		}

	}
#pragma endregion




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
	class Scene *currentScene;
	Scene *menuScene;

	//	michael's playground ahahhahahaha
	std::unique_ptr<FadeTransition> fadeTransition; // frick manual memory management, we quirky pointer
	bool isPaused;

	//	settings default values
	static void setDefaultSettings() {
		settings::FPS = 120;
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
	void StartFadeInTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr);

	//	Fade OUT transition (fade out from black)
	//void StartFadeOutTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr);

	//	loading sound effects to be used in the scenes
	static void LoadSoundEffects() {
		// DEBUG sound effects here
		sfxSound.loadSound("my bike", "sound/test/wait till you see me on my bike.ogg");

		//sound effects here
		sfxSound.loadSound("gameover", "sound/gameover.ogg");
		sfxSound.loadSound("gunshot", "sound/gun-shot.ogg");
		sfxSound.loadSound("slash", "sound/slash.ogg");



		sfxSound.setVolume(settings::SoundEffectVolume);	//	dont touch this 
	}

	//	loading music to be used in the scenes
	static void LoadMusic() {
		// DEBUG sound effects here
		musicSound.loadSound("theme", "sound/test/19. Select Position (Wii Sports).ogg");
		musicSound.loadSound("gyat", "sound/test/gyat.ogg");
		//sound effects here

		musicSound.loadSound("ominous music", "sound/drone-background-music.ogg");
		musicSound.loadSound("overworld music", "sound/exploration-music-loop.ogg");
		musicSound.loadSound("chiptune-y music", "sound/game-soundtrack-4.ogg");
		musicSound.loadSound("retro epic music", "sound/game-soundtrack-5.ogg");
		musicSound.loadSound("chill background music", "sound/lofi-fusion-background-music.ogg");


		musicSound.setVolume(settings::MusicVolume);	//	dont touch this 
	}

	void quitPls() {
		while(settings::isRunning == true) {
			settings::isRunning = false;
		}
	}

};
#endif
