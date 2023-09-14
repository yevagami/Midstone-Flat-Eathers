#include "Hitbox.h"

bool Hitbox::collisionCheck(Hitbox other){
	if (x > other.x + other.w) { return false; }
	if (other.x > x + w) { return false; }

	if (y > other.y + other.h) { return false; }
	if (other.y > y + h) { return false; }

	return true;
}

void Hitbox::onCollision(Hitbox other_) {
	if (collisionCheck(other_)) {
		if (collisionResponse != nullptr) {
			collisionResponse();
		}
		else {
			return;
		}
	}
}