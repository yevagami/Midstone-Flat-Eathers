#pragma once
#include <irrKlang.h>


class Sound {
public:
    Sound() {
        // Initialize the IrrKlang engine
        engine = irrklang::createIrrKlangDevice();
    }

    ~Sound() {
        // Clean up the IrrKlang engine
        if (engine)
            engine->drop();
    }

    // Play a sound effect
    void playSound(const char* soundFile) {
        if (engine) {
            engine->play2D(soundFile);
        }
    }

    // Stop all currently playing sounds
    void stopAllSounds() {
        if (engine) {
            engine->stopAllSounds();
        }
    }

    // Set the master volume for all sounds (0.0 - 1.0)
    void setVolume(float volume) {
        if (engine) {
            engine->setSoundVolume(volume);
        }
    }

private:
    irrklang::ISoundEngine* engine;
};
