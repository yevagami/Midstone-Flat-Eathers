#pragma once
#include <SDL_rect.h>
#include <Vector.h>

namespace MATH {
	struct MATH::Vec3;
}


//	this class could have a default constructor that takes 4 parameters (or an SDL_Rect)...
//	and generates the hitbox from that
//	use it can rely on manual hitbox generation (generateHitbox() method)

class Hitbox{
public: 
	float x;
	float y;
	float w;
	float h;

	bool generateHitbox(const SDL_Rect& rectangle_);

	[[nodiscard]] bool collisionCheck(const Hitbox& other);
	[[nodiscard]] bool collisionClickCheck(float pointX_, float pointY_) const;
	[[nodiscard]] bool collisionClickCheck(const MATH::Vec3& mouseCoords_) const;
};

