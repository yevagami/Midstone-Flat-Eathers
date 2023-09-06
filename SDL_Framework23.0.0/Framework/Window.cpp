#include "Window.h"
#include <iostream>


Window::Window(int width_, int height_, const char* name_) {
	window = nullptr;
	width = width_;
	height = height_;
	name = name_;
}

bool Window::OnCreate() {
	// The following is a typical chunk of code for initialization 
	// a window in SDL
	
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create the window
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Window::OnDestroy() {
	// The following is a typical chunk of code for destroying 
	// an SDL window

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	//Quit SDL subsystems
	SDL_Quit();
}

Window::~Window() {
}

SDL_Window* Window::GetSDL_Window() {
	return window;
}