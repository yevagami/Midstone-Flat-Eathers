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
	bool active = true;
	float x;
	float y;
	float w;
	float h;

	//Why is w,h a float and the x,y position an int??? So I swapped them
	//-Adriel
	//idk but its funny lmao - michael
	//	it also causes a data loss when it converts from int -> float, so im changing it
	Hitbox(const float width_ = 0, const float height_ = 0, const float x_ = 0, const float y_ = 0)
	: x(x_), y(y_), w(width_), h(height_)
	{}
	
	bool generateHitbox(const SDL_Rect& rectangle_);

	[[nodiscard]] bool collisionCheck(const Hitbox* other) const;
	[[nodiscard]] bool collisionClickCheck(float pointX_, float pointY_) const;
	[[nodiscard]] bool collisionClickCheck(const MATH::Vec3& mouseCoords_) const;

};