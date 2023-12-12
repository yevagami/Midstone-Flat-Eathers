#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "GameManager.h"

using namespace MATH;

class Scene {
public:
	const char* name = "";
    class GameManager* game = NULL;


	Scene()
	{} 

	virtual ~Scene()
	{}

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
    virtual void HandleEvents(const SDL_Event& event) = 0;

	virtual float getxAxis() = 0;
	virtual float getyAxis() = 0;
	virtual SDL_Window* getWindow() = 0;
    virtual Matrix4 getProjectionMatrix() = 0;
	virtual Matrix4 getInverseMatrix() = 0;
	virtual SDL_Renderer* getRenderer() = 0;
};

#endif
