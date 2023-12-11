#include "Projectile.h"
#include "Level.h"

Projectile::Projectile(Level* parentLevel_, Vec3 pos_, Vec3 vel_, Vec3 scale_, int w_, int h_, float duration_, float power_){
	parentLevel = parentLevel_;
	pos = pos_;
	vel = vel_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);

	projectileSprite = Sprite("Textures/programmer_art/player_effects_sheet.png", parentLevel->getParentScene()->getRenderer());
	projectileSprite.autoLoadSprites();
	image = projectileSprite.image;
	texture = projectileSprite.texture;
	cutout = &projectileSprite.spriteStorage[Bullet];

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

void Projectile::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {
	//Failsafe incase the programmer forgets to add a texture to the body
	if (texture == nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer_, IMG_Load("Textures/programmer_art/missing_texture.png"));
		std::cout << "You forgot a texture\n";
	}

	//Copied code from OG body.h
	SDL_Rect square;
	Vec3 screenCoords;
	float w, h;
	screenCoords = projectionMatrix_ * pos;
	if (cutout == nullptr) {
		w = image->w * scale.x;
		h = image->h * scale.y;
	}
	else {
		w = cutout->w * scale.x;
		h = cutout->h * scale.y;
	}

	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = static_cast<int>(w);
	square.h = static_cast<int>(h);


	float angle = atan2f(vel.y, vel.x);
	angle = angle * 180.0f / M_PI;
	SDL_RenderCopyEx(renderer_, texture, cutout, &square, -angle, nullptr, SDL_FLIP_NONE);
}
