#include "Body.h"

Body::Body() {}

Body::Body(Vec3 pos_) {
	pos = pos_;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 acc_,
	float mass_, const char* textureFile_) {
	pos = pos_; 
	vel = vel_; 
	acc = acc_;
	mass = mass_; 
	textureFile = textureFile_;
}



void Body::Update(float deltaTime) {
	vel.x += acc.x * deltaTime;
	vel.y += acc.y * deltaTime;
	vel.z += acc.z * deltaTime;
	
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;
	pos.z += vel.z * deltaTime;
}


void Body::LoadHitbox(){
	if (texture != nullptr) {
		SDL_Point point;
		SDL_QueryTexture(texture, nullptr, nullptr, &point.x, &point.y);
		point.x = point.x / 2;
		hitbox = { (int)pos.x, (int)pos.y, point.x, point.y };
	}
}


bool Body::collisionCheck(SDL_Rect other){
	/*
	if (hitbox.y + hitbox.h <= other.y){
		return false;
	}

	if (hitbox.y >= other.y + other.h){
		return false;
	}

	if (hitbox.x + hitbox.w <= other.x){
		return false;
	}

	if (hitbox.x >= other.x + other.w){
		return false;
	}
	*/

	if ((hitbox.y + hitbox.h >= other.y || hitbox.y <= other.y + other.h) &&
		(hitbox.x + hitbox.w >= other.x || hitbox.x <= other.x + other.w)) {
		return true;
	}

	return false;
}


void Body::OnDestory(){
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

const char* Body::GetTextureFile() {
	return textureFile;
}

void Body::SetTextureFile(const char* textureFile_){
	textureFile = textureFile_;
}

Body::~Body() {
}

