// This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "GameManager.h"

using namespace std;

//Screen dimensions
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

// For SDL2 to work in the main function, you need to pass on the following arguments.
// This is a standard C-style entry point. 
int main(int argc, char* args[]){ 

	// Generate a new game manager pointer
	GameManager* game_ptr = new GameManager();
	// Attempt to create a new game visualization
	bool status = game_ptr->OnCreate(SCREEN_WIDTH, SCREEN_HEIGHT, "Testing Window");
	// If the game visualization is on, run the scene inside the game
	if (status) {
		game_ptr->Run();
	}
	else {
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}

	// After the game ends, destroy then delete the game manager pointer
	game_ptr->OnDestroy();
	delete game_ptr;

	return 0;
}

