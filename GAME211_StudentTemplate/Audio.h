#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>


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

	//	the sound engine... public :O
	irrklang::ISoundEngine* engine;

private:
	std::unordered_map<std::string, irrklang::ISoundSource*> soundSources;
};
