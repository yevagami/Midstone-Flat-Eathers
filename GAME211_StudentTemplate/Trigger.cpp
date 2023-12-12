#include "Trigger.h"
#include "Level.h"

Trigger::Trigger(Level* parentScene_, Vec3 pos_, int w_, int h_, std::function<void()> callback_) {
	parentLevel = parentScene_;
	pos = pos_;
	Body::LoadHitbox(w_, h_);
	callback = callback_;

	Sprite triggerSprite = Sprite("Textures/programmer_art/sprite_sheet.png" , parentLevel->getParentScene()->getRenderer());
	triggerSprite.autoLoadSprites();

	image = triggerSprite.image;
	texture = triggerSprite.texture;

	SDL_Rect cutoutFix{ 128, 128 * 5, 128, 128 };
	cutout = &cutoutFix;
};

