#pragma once
#include "Body.h"
class Enemy : public Body{
	Enemy(Level* parentLevel_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_) :
		Body(parentLevel_, pos_, scale_, w_, h_, image_) {
		type = ENEMY;
	}
};

