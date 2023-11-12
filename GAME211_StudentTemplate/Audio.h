#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>

namespace type {
	extern std::string music;
	extern std::string sfx;
	extern std::string test;
}

class Sound {
public:
	Sound
	() : engine(nullptr) {
		//  create the "irrKlang device"
		engine = irrklang::createIrrKlangDevice();
		if (engine) { engine->setSoundVolume(1.0f); }
	}

	~Sound
	() { if (engine) { engine->drop(); } }

	///	play, pause, resume, stop
	void loadSound(const std::string& label_, const char* soundFile_);
	void playSound(const std::string& label_, bool looped_ = false, float volume_ = 1.0f);
	void playSoundDirectly(const char* soundFile_, bool looped_ = false, float volume_ = 1.0f) const;
	void pauseSound(const std::string& label_);
	void resumeSound(const std::string& label_);
	// stops a specific sound by label
	void stopSound(const std::string& label_);
	//  stops all currently playing sounds
	void stopAllSounds() const;

	///	official irrklang supported volume control
	void setVolume(float volume_) const;
	void setGroupVolume(const std::string& groupLabel_, float volume_);
	void createSoundGroup(const std::string& groupLabel_);
	void addToSoundGroup(const std::string& label_, const std::string& groupLabel_);

	/// groups (manual)
	std::unordered_map<std::string, std::vector<std::string>> soundGroups; //	not the map of string to vector<string>
	std::vector<irrklang::ISound*> ambientSounds;
	std::vector<irrklang::ISound*> sfxSounds;
	std::vector<irrklang::ISound*> musicSounds;

	//	the sound engine... public :O
	irrklang::ISoundEngine* engine;

private:
	std::unordered_map<std::string, irrklang::ISoundSource*> soundSources;
};
