#pragma once
#include "Vector.h"
#include "VMath.h"
#include "Hitbox.h"
#include <SDL_image.h>

using namespace MATH;

class Body {
	//Texture stuff
	SDL_Texture* texture = nullptr;
	const char* textureFile = "";
	

public:

	//Collisions
	SDL_Rect hitbox;
	void LoadHitbox(float w_, float h_);
	void drawHitbox(SDL_Renderer* screenRenderer, int screenWidth, int screenHeight, float physicsScreenWidth, float physicsScreenHeight);
	bool collisionCheck(Vec3 pos, Vec3 otherPos, SDL_Rect hitbox, SDL_Rect otherHitbox);
	void collisionResponse(float deltaTime, Body* other);
	bool solid = false;

	// Vectors set to [0,0,0] by their default constructor
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;

	// A mass of 1 kg seems like a good default value
	float mass = 1.0f;

	//Texture methods
	SDL_Texture* GetTexture() { return texture; }
	void SetTexture(SDL_Texture* texture_) { texture = texture_; }

	const char* GetTextureFile();
	void SetTextureFile(const char* textureFile_);


	//Constructors
	Body();
	Body(Vec3 pos_);
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_, const char* textureFile_);
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_, const char* textureFile_, bool solid_);


	void Update(float deltaTime);
	void OnDestory();

	//Destructor
	~Body();

	//

};
