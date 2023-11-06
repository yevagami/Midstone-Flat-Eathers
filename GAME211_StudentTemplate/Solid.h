#pragma once
#ifndef SOLID_H
#define SOLID_H

#include "Body.h"
class Solid : public Body{
public:
	//Constructors
	Solid() {}
	Solid(float x_, float y_, float w_, float h_);
	Solid(Scene* parentScene_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_) : 
		Body(parentScene_, pos_, scale_, w_, h_, image_) {}

	//Override methods
	void OnCollide(Body* other, float deltaTime) override;
};

#endif // !SOLID_H
