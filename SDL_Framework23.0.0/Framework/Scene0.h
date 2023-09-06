#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "Body.h"


class Scene0 : public Scene {

	SDL_Window* window;
	int screenWidth, screenHeight, screenDepth = 1;
	float physicsScreenWidth = 30.0f, physicsScreenHeight = 15.0f, physicsScreenDepth = 0.0f;

	SDL_Renderer* screenRenderer;
	
	// Bodies in the scene
	Body* background;
	Body* car;
	SDL_Texture* backgroundTexture;
	SDL_Texture* carTexture;

	/// <summary>
	/// Load an image into a texture object.
	/// </summary>
	/// <param name="textureFile">image file</param>
	/// <returns>The SDL texture of this image</returns>
	SDL_Texture* loadImage(const char* textureFile);

	/// <summary>
	/// Generate a rectangle that will encompass a scaled version of the image.
	/// </summary>
	/// <param name="objectTexture">Texture object of the image</param>
	/// <param name="start_x">The new x location of the image's upper left corner</param>
	/// <param name="start_y">The new y location of the image's upper left corner</param>
	/// <param name="scale">The new scale of the image (must be 
	/// bwteen 0.0 and 1.0)) </param>
	/// <returns>A rectangle that the image will be rendered inside</returns>
	SDL_Rect scale(SDL_Texture* objectTexture, 
					int start_x = 0, int start_y = 0, float scale = 1.0f);

public:

	/// <summary>
	/// Initiate a new scene.
	/// </summary>
	/// <param name="sdlWindow">The window which this scene will be rendered in.</param>
	Scene0(SDL_Window* sdlWindow);

	/// <summary>
	/// Create the renderer and load the bodies's textures.
	/// </summary>
	/// <returns> Whether this scene has been created.</returns>
	bool OnCreate();

	//// <summary>
	/// Handle the events from keyboard and mouse and change the scene accordingly.
	/// </summary>
	void HandleEvents(const SDL_Event& sdlEvent);

	/// <summary>
	/// Update this scene's obejects. 
	/// </summary>
	/// <param name="time">The current time</param>
	void Update(const float time);

	/// <summary>
	/// Return the screen coordinates of the given physics coordinates
	/// </summary>
	/// <param name="physicsCoords"></param>
	/// <returns></returns>
	Vec3 PhysicsSpaceToScreenSpace(Vec3 physicsCoords);

	/// <summary>
	/// Render this scene on the window. 
	/// </summary>
	void Render();

	/// <summary>
	/// Destroy this scene.
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// Destructor. Delete all pointer attributes in this class
	/// then delete this object.
	/// </summary>
	~Scene0();
};


