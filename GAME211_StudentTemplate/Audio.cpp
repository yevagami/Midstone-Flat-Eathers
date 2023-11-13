#include "Audio.h"

namespace type {
	std::string music = "music";
	std::string sfx = "sfx";
	std::string test = "test";
}

void Sound::loadSound(const std::string& label_, const char* soundFile_) {
	if (engine) {
		if (irrklang::ISoundSource* soundSource = engine->addSoundSourceFromFile(soundFile_)) {
			soundSources[label_] = soundSource;
		}
	}
}

void Sound::playSound(const std::string& label_, const bool looped_, const float volume_) {
	if (engine && soundSources.find(label_) != soundSources.end()) {
		if (irrklang::ISound* sound = engine->play2D(soundSources[label_], looped_)) { sound->setVolume(volume_); }
	}
}

void Sound::playSoundDirectly(const char* soundFile_, const bool looped_, const float volume_) const {
	if (engine) { if (irrklang::ISound* sound = engine->play2D(soundFile_, looped_)) { sound->setVolume(volume_); } }
}

void Sound::pauseSound(const std::string& label_) {
	if (engine && soundSources.find(label_) != soundSources.end()) { engine->setAllSoundsPaused(true); }
}

void Sound::resumeSound(const std::string& label_) {
	if (engine && soundSources.find(label_) != soundSources.end()) { engine->setAllSoundsPaused(false); }
}

void Sound::stopSound(const std::string& label_) {
	if (engine && soundSources.find(label_) != soundSources.end()) {
		engine->stopAllSoundsOfSoundSource(soundSources[label_]);
	}
}

void Sound::stopAllSounds() const { if (engine) { engine->stopAllSounds(); } }

void Sound::setVolume(const float volume_) const { if (engine) { engine->setSoundVolume(volume_); } }

void Sound::setGroupVolume(const std::string& groupLabel_, const float volume_) {
	if (soundGroups.find(groupLabel_) != soundGroups.end()) {
		for (const std::string& soundLabel : soundGroups[groupLabel_]) {
			if (soundSources.find(soundLabel) != soundSources.end()) {
				engine->setSoundVolume(volume_);
			}
		}
	}
}

void Sound::createSoundGroup(const std::string& groupLabel_) { soundGroups[groupLabel_] = std::vector<std::string>(); }

void Sound::addToSoundGroup(const std::string& label_, const std::string& groupLabel_) {
	if (soundSources.find(label_) != soundSources.end()) { soundGroups[groupLabel_].emplace_back(label_); }
}