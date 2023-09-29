#pragma once
#include "Body.h"
#include "Hitbox.h"
#include <SDL_image.h>



//	its so lonely in my mansion :(
class GameObject {
protected:
	//	Texture stuff (stolen from body)
	SDL_Texture* texture = nullptr;
	const char* textureFile = "";

	bool 
		isActive,	//	should this object be active? is it going to be put through update();
		isSolid;		//	is the hitbox active?

	const char 
		*name;

public:
		//	Constructors
	GameObject();

	GameObject(const char* objectName, Vec3 position); // given a name and a position
	GameObject(const char *objectName, Vec3 position, const char* textureFile, bool isActive, bool isSolid); // given a name, position, textureFileDir, isActive bool, and an isSolid bool

	//	SDL Functions
	virtual void OnCreate();
	virtual void Update();
	virtual void HandleEvents(const SDL_Event* events);
	virtual void OnDestroy();

public:
	void LoadHitbox(float w_, float h_);


	protected:
		//	sub-components
	Body body; //	physPos, screenPos vel, accel, 
	Hitbox hitbox; //	hitbox
};



class Entity : public GameObject {
protected: 
	float 
		maxHealth,
		defaultHealth,
		currentHealth;

protected:
	void setMaxHealth(float newMaxHealth);
	void setDefaulyHealth(float newDefaultHealth);
	void setCurrentHealth(float newCurrentHealth);


};