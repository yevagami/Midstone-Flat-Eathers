#include "Projectile.h"
#include <SDL_image.h>
#include "Level.h"

Projectile::Projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_){
	parentLevel = parentLevel_;
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);
	image = IMG_Load("Textures/programmer_art/void_cat.png");
	texture = SDL_CreateTextureFromSurface(parentLevel->getParentScene()->getRenderer(), image);
	type = PROJECTILE;
	duration_timer = new Clock(duration, false);
	duration_timer->Start();
}

Projectile::Projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_, SDL_Surface* image_) {
	parentLevel = parentLevel_;
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);
	image = image_;
	texture = SDL_CreateTextureFromSurface(parentLevel->getParentScene()->getRenderer(), image);
	type = PROJECTILE;
	duration_timer = new Clock(duration, false);
	duration_timer->Start();
}

void Projectile::Update(float deltaTime){
	duration_timer->Update(deltaTime);
	if (duration_timer->completed && !destroyFlag) {
		destroyFlag = true;
	}

	if (destroyFlag) {
		parentLevel->trashBodies.push_back(this);
	}

	Body::Update(deltaTime);
}

void Projectile::OnCollide(Body* other, float deltaTime){
	if (other->type == SOLID) {
		destroyFlag = true;
	}
	
}

void Projectile::OnDestroy(){
	delete duration_timer;
	Body::OnDestroy();
}
