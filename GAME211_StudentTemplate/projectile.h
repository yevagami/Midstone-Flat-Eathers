#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Body.h"
#include "Clock.h"

class projectile : public Body{
public:
	//constructors
	//Constructor requiring the bare minimum to make the projectile work
	projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_);

	//Constructor requiring the bare minimum to make the projectile work
	projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_, SDL_Surface* image_);

	//Override methods
	void Update(float deltaTime) override;
	void OnCollide(Body* other, float deltaTime) override;
	void OnDestroy() override;
private:
	bool destroyFlag = false;
	float duration = 3.0f;
	Clock* duration_timer = nullptr;
};

#endif
