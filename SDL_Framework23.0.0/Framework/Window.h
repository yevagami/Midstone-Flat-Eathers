#pragma once
#include <SDL.h>

class Window {
	SDL_Window* window;
	int width, height;
	const char* name;

public:

	/// <summary>
	/// Create a window with the given width, height, and name.
	/// </summary>
	/// <param name="width_">Window's width</param>
	/// <param name="height_">Window's height</param>
	/// <param name="name_">Window's name</param>
	Window(int width_, int height_, const char* = "First Window");

	/// <summary>
	/// Destructor. 
	/// </summary> 
	~Window();

	/// <summary>
	/// Intialize an SDL window
	/// </summary>
	/// <returns> Whether this window has been intialized successfully.</returns>
	bool OnCreate();

	/// <summary>
	/// Destroy this window
	/// </summary>
	void OnDestroy();

	/// <returns> The SDL window associated with this window.</returns>
	SDL_Window* GetSDL_Window();
};
