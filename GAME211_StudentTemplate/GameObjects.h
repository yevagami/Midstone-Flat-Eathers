#pragma once
#include "Body.h"

//	its so lonely in my mansion :(
class GameObject : public Body {
public:

	GameObject(const GameObject& otherObject_) = default;

	GameObject() : Body(Transform{})
	{}

	explicit GameObject(const Body& body_);

	~GameObject() override
	{}

	void Update(float deltaTime_) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_, float scale_ = 1.0f) override;
	void HandleEvents(const SDL_Event& event_) override;

protected:

public:

	bool isActive;


};



