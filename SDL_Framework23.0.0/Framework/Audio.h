#pragma once
#include <vector>
#include <string>
#include "SDL.h"



#include "ConsistentConsole.h"
#include "PrettyPrinting.h"


//  USING
#include "SDL_mixer.h"
//  MAKE A CLASS THAT LETS U GIVE A DIRECTORY AND IT PLAYS THAT SOUND EFFECT
//  fill out the class <3
//   i believe in you.



class Audio {
protected:

public:
    
    Audio();
    ~Audio();

	void playSound(const char* fileDirectory);
    void playSoundAt(const char* fileDirectory, float position);

    void stopSound();

    void pauseSound();
    void continueSound();


};

