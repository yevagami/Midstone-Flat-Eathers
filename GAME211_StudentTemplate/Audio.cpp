#include "Audio.h"
#include <algorithm>


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

bool Sound::isPlaying() const {
	for(const auto& pair : soundSources) {
		if(engine->isCurrentlyPlaying(pair.second)) {
			return true;
		}
	}

	return false;
}

bool Sound::isPlayingExperimental() const {
	return std::any_of(soundSources.begin(), soundSources.end(),
		[this](const auto& pair) { return engine->isCurrentlyPlaying(pair.second); });
}

