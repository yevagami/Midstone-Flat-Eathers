#pragma once
class Hitbox{
public: 
	float x;
	float y;
	float w;
	float h;
	void (*collisionResponse)();
	void onCollision(Hitbox other_);
	bool collisionCheck(Hitbox other);
};

