#include "Solid.h"

Solid::Solid(Vec3 pos_, float w_, float h_) {
	pos = pos_;
	Body::LoadHitbox(w_, h_);
}

void Solid::OnCollide(Body* other, float deltaTime){
	if (other->type == PROJECTILE) { return; }
	//Pushes the body that's collided with it back
	//Just like newton's third law 
	Vec3 otherVel = other->getVel();
	Vec3 otherPos = other->getPos();

	Vec3 newPos = otherPos + -1 * otherVel * deltaTime;
	other->setPos(newPos);
	other->setVel(Vec3());
}
