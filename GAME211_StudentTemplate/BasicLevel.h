#ifndef BASICLEVEL_H
#define BASICLEVEL_H
#include "Solid.h"
#include "PlayerBody.h"

class BasicLevel
{
private:

public:

	//Fundamental methods (create, update, render, handle input, destroy)
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float time);
	virtual void Render();
	virtual void HandleEvents(const SDL_Event& event);

};
#endif