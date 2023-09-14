#include "Body.h"

Body::Body() {}

Body::Body(Vec3 pos_) {
	pos = pos_;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, const char* textureFile_, bool solid_){
	pos = pos_; 
	vel = vel_; 
	acc = accel_;
	mass = mass_; 
	textureFile = textureFile_;
	solid = solid_;
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

	screenPos.x = (pos.x * screenDimensions.x) / virtualDimensions.x;
	screenPos.y = ((virtualDimensions.y - pos.y) * screenDimensions.y)/ virtualDimensions.y ;
	screenPos.z = (pos.z * screenDimensions.z) / virtualDimensions.z;

	hitbox.x = screenPos.x;
	hitbox.y = screenPos.y;
}


void Body::LoadHitbox(float w_, float h_){
	hitbox.w = w_;
	hitbox.h = h_;
}


void Body::drawHitbox(SDL_Renderer* screenRenderer, int screenWidth, int screenHeight, float physicsScreenWidth, float physicsScreenHeight){
	return;
}


void Body::collisionResponse(float deltaTime, Body* other_){
	std::cout << "Collided\n";
	if (other_->solid) {
		pos.x -= vel.x * deltaTime;
		pos.y -= vel.y * deltaTime;
		pos.z -= vel.z * deltaTime;
	}
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

Body::~Body() {}

