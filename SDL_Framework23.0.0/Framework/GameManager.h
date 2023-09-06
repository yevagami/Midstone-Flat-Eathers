#pragma once
#include "Scene.h"
#include "Window.h"
#include "Timer.h"


/// <summary>
/// A class that manages the screen to render a scene
/// </summary>
class GameManager {

	/// private attributes
	Window* windowPtr;
	Timer* timer;
	bool isRunning;
	Scene* currentScene;

public:

	/// <summary>
	/// Initiate a game manager object.
	/// </summary>
	GameManager();

	/// <summary>
	/// Destructor. 
	/// </summary> 
	~GameManager();

	/// <summary>
	/// Create a game manager.
	/// </summary>
	/// <param name="width_">Window's width</param>
	/// <param name="height_">Window's height</param>
	/// <param name="window_name">Window's name</param>
	/// <returns> Whether this game manager has been created successfully</returns>
	bool OnCreate(int width_, int height_, const char* window_name = "First Window");

	/// <summary>
	/// Destroy this game manager along with its elements. 
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// Run the scene in this game manager
	/// </summary>
	void Run();
};