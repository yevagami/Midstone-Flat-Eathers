#include "Projectile.h"
#include "Level.h"

Projectile::Projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_, float power_){
	parentLevel = parentLevel_;
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);

	projectileSprite = Sprite("Textures/programmer_art/sprite_sheet.png", parentLevel->getParentScene()->getRenderer());
	projectileSprite.autoLoadSprites();
	image = projectileSprite.image;
	texture = projectileSprite.texture;
	cutout = &projectileSprite.spriteStorage[projectile];

	type = PROJECTILE;
	power = power_;
	duration_timer = new Clock(duration, false, [this]() {
		if (!destroyFlag) { destroyFlag = true; }
	});
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
	duration_timer = new Clock(duration, false, [this](){
		if (!destroyFlag) { destroyFlag = true; }
	});
	duration_timer->Start();
}


void Projectile::Update(float deltaTime){
	//Updates the timer
	duration_timer->Update(deltaTime);
	Body::Update(deltaTime);
	if (VMath::mag(vel) == 0) {
		cout << "Huh???\n";
	}
}

void Projectile::OnCollide(Body* other, float deltaTime){
	//If it's a solid, just destroy itself
	if (other->type == SOLID) {
		destroyFlag = true;
	}

	//if it's an enemy, hurt it then destroy itself
	if (other->type == ENEMY) {
		other->takeDamage(power);
		destroyFlag = true;
	}
	
}

void Projectile::OnDestroy(){
	delete duration_timer;
	Body::OnDestroy();
}
