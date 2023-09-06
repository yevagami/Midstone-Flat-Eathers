#pragma once
#include <iostream>
#include <SDL.h>


class Scene {
public:
	/// <summary>
	/// Create a scene.
	/// </summary>
	/// <returns> Whether this scene has been created</returns>
	virtual bool OnCreate() = 0;

	/// <summary>
	/// Handle the events from keyboard and mouse and change the scene accordingly.
	/// </summary>
	virtual void HandleEvents(const SDL_Event& sdlEvent) = 0;

	/// <summary>
	/// Update this scene.
	/// </summary>
	/// <param name="time">The current time</param>
	virtual void Update(const float time) = 0;

	/// <summary>
	/// Render this scene on the screen
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// Destroy this scene.
	/// </summary>
	virtual void OnDestroy() = 0;

	/// <summary>
	/// Delete this class object
	/// </summary>
	virtual ~Scene() {
		std::cout << "deleting Scene class." << std::endl;
	}

};