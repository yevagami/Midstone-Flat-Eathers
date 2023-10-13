#pragma once
#include "SDL.h"

#include <vector>
#include <string>
#include <functional>
#include <memory>


//
/// BARELY WORKS...
/// i...    h a t e...  sdl audio...
/// off the interwebs *thunder*
//


class Audio : public std::enable_shared_from_this<Audio> {
public:
    Audio(const int activeSoundEffectVolume_ = 100)
        : activeSoundEffectVolume(activeSoundEffectVolume_) {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            // Handle SDL initialization error.
            isSDLInitialized = true;
        }

        SDL_AudioSpec desiredSpec;
        desiredSpec.freq = 44100;
        desiredSpec.format = AUDIO_S16SYS;
        desiredSpec.channels = 2;
        desiredSpec.samples = 2048;
        desiredSpec.callback = AudioCallback;
        desiredSpec.userdata = this;
        if (SDL_OpenAudio(&desiredSpec, NULL) < 0) {
            // Handle SDL audio initialization error.
            isAudioInitialized = true;
        }

        SDL_PauseAudio(0); // Start audio playback.
        totalChannels = desiredSpec.channels;

        // Initialize channels.
        allChannelStates.resize(totalChannels, false);
        channelSounds.resize(totalChannels);
    }

    ~Audio() {
        SDL_CloseAudio();
        SDL_Quit();
    }

    bool playSound(const char* soundFileDirectory_) {
        SDL_LockAudio();

        // Load the sound effect.
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8* wavBuffer;
        if (SDL_LoadWAV(soundFileDirectory_, &wavSpec, &wavBuffer, &wavLength) == NULL) {
            SDL_UnlockAudio();
            return false; // Error loading sound effect.
        }

        // Find an available channel.
        int channel = findAvailableChannel();
        if (channel == -1) {
            SDL_UnlockAudio();
            SDL_FreeWAV(wavBuffer);
            return false; // No available channel.
        }

        // Set the volume by scaling the audio samples.
        for (Uint32 i = 0; i < wavLength; i += 2) {
            Sint16* sample = reinterpret_cast<Sint16*>(wavBuffer + i);
            *sample = static_cast<Sint16>(*sample * activeSoundEffectVolume / 100);
        }

        // Play the sound effect only if the channel is not already active.
        if (!allChannelStates[channel]) {
            channelSounds[channel] = std::make_pair(wavBuffer, wavLength);
            allChannelStates[channel] = true; // Set the channel as active.
        }

        SDL_UnlockAudio();

        return true;
    }


    bool stopSound() {
        SDL_LockAudio();

        // Stop all channels.
        for (int i = 0; i < totalChannels; i++) {
            if (i >= 0 && i < totalChannels) {
                if (allChannelStates[i] && channelSounds[i].first != nullptr) {
                    SDL_FreeWAV(channelSounds[i].first);
                    channelSounds[i].first = nullptr;
                    allChannelStates[i] = false;
                }
            }
        }

        SDL_UnlockAudio();
        return true;
    }

    std::function<void(int)> soundFinishedCallback;

    std::shared_ptr<Audio> getShared() {
        return shared_from_this();
    }

protected:
    int totalChannels;
    std::vector<bool> allChannelStates;
    std::vector<std::pair<Uint8*, Uint32>> channelSounds;

    bool isSDLInitialized = false;
    bool isAudioInitialized = false;

    int activeSoundEffectVolume;

    int findAvailableChannel() {
        for (int i = 0; i < totalChannels; i++) {
            if (!allChannelStates[i]) {
                return i;
            }
        }
        return -1; // No available channel.
    }

    static void AudioCallback(void* userData, Uint8* stream, int len) {
        auto shared = static_cast<Audio*>(userData)->getShared();
        for (int i = 0; i < shared->totalChannels; i++) {
            if (shared->allChannelStates[i]) {
                Uint32 lengthToCopy = std::min(static_cast<Uint32>(len), shared->channelSounds[i].second);

                if (lengthToCopy > 0) {
                    SDL_memcpy(stream, shared->channelSounds[i].first, lengthToCopy);
                    shared->channelSounds[i].first += lengthToCopy;
                    shared->channelSounds[i].second -= lengthToCopy;

                    if (shared->channelSounds[i].second == 0) {
                        // Reset the position of the sound.
                        SDL_FreeWAV(shared->channelSounds[i].first);
                        shared->channelSounds[i].first = nullptr;
                        shared->allChannelStates[i] = false;

                        // Notify that the sound has finished playing.
                        if (shared->soundFinishedCallback) {
                            shared->soundFinishedCallback(i);
                        }
                    }
                }
            }
            else if (shared->channelSounds[i].first != nullptr) {
                // Sound was not marked as playing, but data remains, free it.
                SDL_FreeWAV(shared->channelSounds[i].first);
                shared->channelSounds[i].first = nullptr;

                // Notify that the sound has finished playing (it was stopped).
                if (shared->soundFinishedCallback) {
                    shared->soundFinishedCallback(i);
                }
            }
        }
    }


};
