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


//	global classes
	inline Sound musicSound;
	inline Sound sfxSound;
	inline ConsistentConsole cc(true, "GameManager.h");
	inline PrettyPrinting pp(pink, purple, cyan);
	inline FileManager file;


#pragma region settings
	namespace options {
		inline const char* settingsFileDirectory = "SaveData/settings.txt";
		inline vector<string> settingsFileContents;

		inline constexpr float MaxVolume = 1.0f;
		inline float MasterVolume;
		inline float MusicVolume;
		inline float SoundEffectVolume;

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

		inline void ApplyDefaultSettings() {
			float DefaultMasterVolume = 0.5f;
			float DefaultSoundEffectVolume = 0.5f;
			float DefaultMusicVolume = 0.5f;
			int DefaultFPS = 60;

			FPS = DefaultFPS;

			MasterVolume = DefaultMasterVolume;
			MusicVolume = DefaultMusicVolume;
			SoundEffectVolume = DefaultSoundEffectVolume;

		}

		inline bool SaveAllSettigns() {
			if (file.fileCheck(settingsFileDirectory)) {
				string newFps = std::to_string(options::FPS);
				string newMastV = std::to_string(options::MasterVolume);
				string newMusV = std::to_string(options::MusicVolume);
				string newSfxV = std::to_string(options::SoundEffectVolume);

				if(settingsFileContents.empty()) {
					newFps = file.stringReformat("fps", newFps);
					newMastV = file.stringReformat("mastervolume", newMastV);
					newMusV = file.stringReformat("musicvolume", newMusV);
					newSfxV = file.stringReformat("sfxvolume", newSfxV);

					settingsFileContents.emplace_back(newFps);
					settingsFileContents.emplace_back(newMastV);
					settingsFileContents.emplace_back(newMusV);
					settingsFileContents.emplace_back(newSfxV);
				} else {
					settingsFileContents = file.replaceValue("fps", newFps, settingsFileContents);
					settingsFileContents = file.replaceValue("mastervolume", newMastV, settingsFileContents);
					settingsFileContents = file.replaceValue("musicvolume", newMusV, settingsFileContents);
					settingsFileContents = file.replaceValue("sfxvolume", newSfxV, settingsFileContents);
				}

				if (file.fileWrite(settingsFileContents, settingsFileDirectory)) {
					if(cc.getConsoleState()) {
						for (const string& settings : settingsFileContents) { cc.log(update, "setting saved", settings); }
					}
					return true;
				}
			}
			return false;
		}
		inline void LoadAllSettigns(vector<string>& superVector_) {
			superVector_ = file.parseTHIS(settingsFileDirectory);

			//	1. read
			string newFps = file.isWhat("fps", superVector_);
			string newMasterVolume = file.isWhat("mastervolume", superVector_);
			string newMusicVolume = file.isWhat("musicvolume", superVector_);
			string newSfxVolume = file.isWhat("sfxvolume", superVector_);

			//	2. write
			FPS = stoi(newFps);
			MasterVolume = stof(newMasterVolume);
			MusicVolume = stof(newMusicVolume);
			SoundEffectVolume = stof(newSfxVolume);
		}

		inline bool loadSettingToVector(vector<string>& superVector_) {
			if(file.fileCheck(settingsFileDirectory)) {
				file.fileLoadToVector(superVector_, settingsFileDirectory);
				return true;

			}
			return false;
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
	void StartFadeInTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr, const std::function<void()>& callfront_ = nullptr);

	//	Fade OUT transition (fade out from black)
	//void StartFadeOutTransition(const Uint64 fadeTime_, const std::function<void()>& callback_ = nullptr);


	//	loading sound effects to be used in the scenes
	static void LoadSoundEffects() {
		// DEBUG sound effects here - Michael
		sfxSound.loadSound("my bike", "sound/test/wait till you see me on my bike.ogg");

		//	load audio into the sfx SuperMap(tm)
		sfxSound.loadSound("gameover", "sound/unnormalized/gameover.ogg");
		sfxSound.loadSound("gunshot", "sound/unnormalized/gun-shot.ogg");
		sfxSound.loadSound("slash", "sound/unnormalized/slash.ogg");
		sfxSound.loadSound("equip", "sound/unnormalized/item-equip.ogg");
		sfxSound.loadSound("shield", "sound/unnormalized/shieldmaiden.ogg");
		sfxSound.loadSound("select", "sound/unnormalized/menu select.ogg");
		sfxSound.loadSound("accept", "sound/unnormalized/interface.ogg");
		sfxSound.loadSound("error", "sound/unnormalized/menu error.ogg");
		sfxSound.loadSound("poof", "sound/unnormalized/poof.ogg");
		sfxSound.loadSound("death", "sound/unnormalized/death.ogg"); // changed the label 
		sfxSound.loadSound("hurt", "sound/unnormalized/hurt.ogg");	//	changed the label
		sfxSound.loadSound("oof", "sound/unnormalized/oof.ogg");


		//	set the sfx irrklang engine to the current sound effect volume
		sfxSound.setVolume(options::SoundEffectVolume);	//	dont touch this 
	}

	static void LoadMusic() {
		// DEBUG sound effects - Michael
		musicSound.loadSound("theme", "sound/test/19. Select Position (Wii Sports).ogg");
		musicSound.loadSound("gyat", "sound/test/gyat.ogg");

		//load audio into the music SuperMap(tm) here
		musicSound.loadSound("ominous music", "sound/unnormalized/drone-background-music.ogg");
		musicSound.loadSound("overworld music", "sound/unnormalized/exploration-music-loop.ogg");
		musicSound.loadSound("chiptune-y music", "sound/unnormalized/game-soundtrack-4.ogg");
		musicSound.loadSound("retro epic music", "sound/unnormalized/game-soundtrack-5.ogg");
		musicSound.loadSound("chill background music", "sound/unnormalized/lofi-fusion-background-music.ogg");
		musicSound.loadSound("battle music", "sound/unnormalized/battle-theme.ogg");


		//	set the music irrklang engine to the current music volume
		musicSound.setVolume(options::MusicVolume);	//	dont touch this 
	}

	//	while the game's running... STOP RUNNING
	static void quitPls() {
		while(options::isRunning == true) {
			options::isRunning = false;
		}
	}

	static void savePls() { 
		options::SaveAllSettigns();
	}

};
#endif
