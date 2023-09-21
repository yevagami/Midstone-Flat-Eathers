#pragma once
#include <vector>
#include <string>
#include "SDL.h"


#include "ConsistentConsole.h"
#include "PrettyPrinting.h"


///	the in-progress audio handling class. just put everything audio related here *for now*.


class Audio {
protected:
	std::vector<std::string> audioDirectories;
	const char* audioDirectory;

	SDL_AudioDeviceID device; // the audio device id
	SDL_AudioSpec spec; // the audio specification
	double phase; // the current phase of the sine wave
	double freq; // the frequency of the sine wave
	int samples; // the number of samples left to play

public:
	std::vector<std::string> getAudioDirectories();
	const char* getAudioDirectory();



protected:
	///	Variables
	//volume
	//pitch
	//y a w
	//more

public:

	Audio();
	~Audio();

};

