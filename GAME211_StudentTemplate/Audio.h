#pragma once
#include "SDL_mixer.h"

#include <vector>

//  constructor initiatizer list (in progress, not implemented)
struct Volume {
    int activeMusicVolume;
    int activeSoundEffectVolume;

    Volume(const int musicVolume_ = 0, const int soundVolume_ = 0)
	: activeMusicVolume(musicVolume_), activeSoundEffectVolume(soundVolume_)
	{}

    ~Volume() = default;
};

class Audio {
public:
    //  mp3 for size, wav for quality, ogg for a balance between size and quality
    Audio(const int activeMusicVolume_ = 0, const int activeSoundEffectsVolume_ = 0, const int totalChannels_ = 10)
	: music(nullptr), totalChannels(totalChannels_),
	defaultMusicVolume(100), defaultSoundEffectVolume(100),
	activeMusicVolume(activeMusicVolume_), activeSoundEffectVolume(activeSoundEffectsVolume_) {

        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) { isSDLInitalized = true; }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { isMixerInitialized = true; }

        if(activeMusicVolume == 0) { activeMusicVolume = defaultMusicVolume; }
        if(activeSoundEffectVolume == 0) { activeSoundEffectVolume = defaultSoundEffectVolume; }

    }

    ~Audio() { 
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    //  play a sound effect
    auto playSound(const char* soundFileDirectory_) -> bool;
    //  play a sound effect in channel...
    auto playSound(const char* soundFileDirectory_, int channel_) -> bool;
    //  attach the sound to a target (positional sound)
    auto playSoundAt(const char* fileDirectory_, float playerX_, float playerY_, float targetX_, float targetY_) -> bool;

    auto stopSound() -> bool;

    void pauseSound();

protected:
    std::vector<Mix_Chunk*> allSoundEffects;
    Mix_Music* music;
    int totalChannels;
    std::vector<bool> allChannelStates;

    // ReSharper disable once CppInconsistentNaming
    bool isSDLInitalized;
    bool isMixerInitialized;

    //  the default volume to play music at
    int defaultMusicVolume;
    //  the default volume to play sfx at
    int defaultSoundEffectVolume;
public:
    //  the volume music is played at
    int activeMusicVolume;
    //  the volume sfx are played at
    int activeSoundEffectVolume;
};

