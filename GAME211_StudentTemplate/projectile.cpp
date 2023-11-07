#include "projectile.h"

projectile::projectile(Scene* parentscene_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_){
	Body::setParentScene(parentscene_);
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);
}

projectile::projectile(Scene* parentscene_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, SDL_Surface* image_) {
	Body::setParentScene(parentscene_);
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);
	image = image_;
}

void projectile::OnCollide(Body* other, float deltaTime){
	return;
}

void projectile::OnDestroy(){
	return;
}
