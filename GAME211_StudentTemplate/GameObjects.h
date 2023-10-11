#pragma once
#include "Body.h"
#include <SDL_image.h>


//	its so lonely in my mansion :(
class GameObject : public Body {
public:

	GameObject() : Body()
	{}

	GameObject(const GameObject& otherObject_) = default;


	~GameObject() override
	{}


	void Update(float deltaTime_) override;

	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_, float scale_ = 1.0f) override;


protected:

};



