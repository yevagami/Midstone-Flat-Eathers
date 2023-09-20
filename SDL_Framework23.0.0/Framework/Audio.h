#pragma once
#include <vector>
#include <string>


#include "ConsistentConsole.h"
#include "PrettyPrinting.h"


///	the in-progress audio handling class. just put everything audio related here *for now*.


class Audio {
protected:
	std::vector<std::string> audioDirectories;
	const char* audioDirectory;
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

