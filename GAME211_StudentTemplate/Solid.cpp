#include "Solid.h"

Solid::Solid(float x_, float y_, float w_, float h_) {
	pos.x = x_;
	pos.y = y_;
	Body::LoadHitbox(w_, h_);
}

void Solid::OnCollide(Body* other, float deltaTime){
	Vec3 otherVel = other->getVel();
	Vec3 otherPos = other->getPos();
	other->setPos(Vec3(
		otherPos.x - otherVel.x * deltaTime,
		otherPos.y - otherVel.y * deltaTime,
		otherPos.z - otherVel.z * deltaTime
	));
}
