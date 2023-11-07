#include "Hitbox.h"
#include "VMath.h"

bool Hitbox::generateHitbox(const SDL_Rect& rectangle_) {
    if (rectangle_.w >= 0 && rectangle_.h >= 0) {
        x = static_cast<float>(rectangle_.x);
        y = static_cast<float>(rectangle_.y);
        w = static_cast<float>(rectangle_.w);
        h = static_cast<float>(rectangle_.h);

        return true;
    }

    return false;
}


bool Hitbox::collisionCheck(const Hitbox* other) const {
	const bool collisionX = x + w >= other->x &&
        other->x + other->w >= x;

    const bool collisionY = y + h >= other->y &&
        other->y + other->h >= y;
    
    return collisionX && collisionY;
}


bool Hitbox::collisionClickCheck(const float pointX_, const float pointY_) const {
	const bool isXInsideBox = (pointX_ >= x) && (pointX_ <= x + w);
	const bool isYInsideBox = (pointY_ >= y) && (pointY_ <= y + h);
    return isXInsideBox && isYInsideBox;
}


bool Hitbox::collisionClickCheck(const MATH::Vec3& mouseCoords_) const {
    return (mouseCoords_.x >= x && mouseCoords_.x <= x + w) //  checking the mouse's x coord to see if its within hitbox
        &&
        (mouseCoords_.y >= y && mouseCoords_.y <= y + h); //    same for y, then return true if both are true
}