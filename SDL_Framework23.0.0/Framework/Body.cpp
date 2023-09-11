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


void Body::LoadHitbox(float w_, float h_){
	width = w_;
	height = h_;
}


void Body::drawHitbox(SDL_Renderer* screenRenderer, int screenWidth, int screenHeight, float physicsScreenWidth, float physicsScreenHeight){
	return;
}


bool Body::collisionCheck(Body* other, int screenHeight){
	float selfY = screenHeight - pos.y;
	float otherY = screenHeight - other->pos.y;

	if (pos.x > other->pos.x + other->width)
	{
		return false;
	}

	if (selfY > otherY + other->height)
	{
		return false;
	}

	if (other->pos.x > pos.x + width)
	{
		return false;
	}

	if (otherY > selfY + height)
	{
		return false;
	}

	return true;
}


void Body::collisionResponse(float deltaTime) {
	std::cout << "Collided\n";
	pos.x -= vel.x * deltaTime;
	pos.y -= vel.y * deltaTime;
	pos.z -= vel.z * deltaTime;
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

