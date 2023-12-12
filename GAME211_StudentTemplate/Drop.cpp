#include "Drop.h"
#include "Level.h"

Drop::Drop(Level* parentLevel_, Vec3 pos_, Vec3 scale_, int w_, int h_, DropType dropType_) {
	parentLevel = parentLevel_;
	pos = pos_;
	scale = scale_;
	Body::LoadHitbox(w_, h_);
	type = DROP;

	dropSprite = Sprite("Textures/programmer_art/player_effects_sheet.png", parentLevel->getParentScene()->getRenderer());
	dropSprite.autoLoadSprites();
	image = dropSprite.image;
	texture = dropSprite.texture;

	dropType = dropType_;
	cutout = &dropSprite.spriteStorage[dropTypeDefs[dropType]];
}

void Drop::OnCollide(Body* other, float deltaTime) {
	if (other->type == PLAYER) {
		destroyFlag = true;

	}
}

void Drop::OnDestroy() {
}
