#pragma once
#include "Body.h"
#include "Hitbox.h"
#include <SDL_image.h>

//	steal the structure of gails body / playerbody classes >:)
//or just migrate to it in entirely

//	its so lonely in my mansion :(
class GameObject {
protected:
	//	Texture stuff (stolen from body)
	SDL_Texture* texture;
	const char* textureFile;

	bool 
		isActive,		//	should this object be active? is it going to be put through update();
		isSolid;			//	is the hitbox active?

	const char 
		*name;

public:
	 // Constructors
	// given a name and a position
	GameObject(const char* objectName); 
	// given a name, a position, and a texture file
	GameObject(const char* objectName, const char* textureFile_); 
	// given a name, position, textureFileDir, isActive bool, and an isSolid bool
	GameObject(const char *objectName, const char* textureFile_, bool isActive_, bool isSolid_); 

	~GameObject() {};

	//	SDL Functions
	void OnCreate();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event* events);
	void OnDestroy();


	void LoadHitbox(float w_, float h_);

#pragma region getters and setters

public:
	//	bools
	bool getIsSolid();
	void setIsSolid(bool state);
	bool getIsActive();
	void setIsActive(bool state);

	//	c_str
	const char* getName();
	void setName(const char* newName);

	//	Texture
	SDL_Texture* getSDLTexture();
	void setSDLTexture(SDL_Texture* newTexture);	
	const char* getTextureFile();	
	void setTextureFile(const char* newTextureFile);	

#pragma endregion

protected:
	//Body body;		 //	physPos, screenPos, mass, vel, accel, 
	Hitbox hitbox;	 //	hitbox
};

//class Entity : public GameObject {
//public:
//
//	//void Update();
//	//void HandleEvents(const SDL_Event* events);
//	//void OnCreate();
//	//void OnDestroy();
//
//protected: 
//	float 
//		maxHealth,
//		defaultHealth,
//		currentHealth;
//
//protected:
//	void setMaxHealth(float newMaxHealth);
//	void setDefaulyHealth(float newDefaultHealth);
//	void setCurrentHealth(float newCurrentHealth);
//
//
//};