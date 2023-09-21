#pragma once
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_mixer.h"


#include "ConsistentConsole.h"
#include "PrettyPrinting.h"


///	the in-progress audio handling class. just put everything audio related here *for now*.


class Audio {
protected:
	//std::vector<std::string> audioDirectories;
	//const char* audioDirectory;
public:
	//std::vector<std::string> getAudioDirectories();
	//const char* getAudioDirectory();

protected:
	Mix_Chunk* chunk; // the sound effect object

public:

    Audio(const char* fileDir);
    ~Audio();

	void playSound(int times);

};

