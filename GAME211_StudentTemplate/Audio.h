#pragma once
#include <irrKlang.h>
#include <unordered_map>
#include <string>


class Sound {
public:
	Sound() : engine(nullptr) {
		//  create the irrKlang device
		engine = irrklang::createIrrKlangDevice();
		if (engine) {
			engine->setSoundVolume(1.0f);
		}
	}

	~Sound() { if (engine) { engine->drop(); } }


	void loadSound(const std::string& label_, const char* soundFile_) {
		if (engine) {
			irrklang::ISoundSource* soundSource = engine->addSoundSourceFromFile(soundFile_);
			if (soundSource) {
				soundSources[label_] = soundSource;
			}
		}
	}

	void playSound(const std::string& label_, const bool looped_ = false, const float volume_ = 1.0f) {
		if (engine && soundSources.find(label_) != soundSources.end()) {
			irrklang::ISound* sound = engine->play2D(soundSources[label_], looped_);
			if (sound) {
				sound->setVolume(volume_);
			}
		}
	}

	//  plays a 2D sound effect
	void playSoundDirectly(const char* soundFile_, const bool looped_ = false, const float volume_ = 1.0f) const {
		if (engine) {
			if (irrklang::ISound* sound = engine->play2D(soundFile_, looped_)) {
				sound->setVolume(volume_);
			}
		}
	}


	// Stop a specific sound by label
	void stopSound(const std::string& label_) {
		if (engine && soundSources.find(label_) != soundSources.end()) {
			engine->stopAllSoundsOfSoundSource(soundSources[label_]);
		}
	}


	//  stops all currently playing sounds
	void stopAllSounds() const {
		if (engine) {
			engine->stopAllSounds();
		}
	}

	// Set the master volume for all sounds (0.0 - 1.0)
	void setVolume(const float volume_) const {
		if (engine) {
			engine->setSoundVolume(volume_);
		}
	}

private:
	irrklang::ISoundEngine* engine;
	std::unordered_map<std::string, irrklang::ISoundSource*> soundSources;
};
