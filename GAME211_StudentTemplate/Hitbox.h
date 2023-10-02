#pragma once



class Hitbox{
public: 
	float x;
	float y;
	float w;
	float h;
	bool collisionCheck(Hitbox other);
};

