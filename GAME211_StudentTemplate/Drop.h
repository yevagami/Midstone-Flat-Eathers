#pragma once
#ifndef DROP_H
#define DROP_H

#include "Body.h"
#include <unordered_map>
class Drop : public Body{
public:
	enum DropType {
		HEALTH = 0,
		POINTS = 1
	};
	DropType dropType;

	std::unordered_map<DropType, SpriteDefinitions> dropTypeDefs = {
		{HEALTH, health},
		{POINTS, points}
	};

	Drop() {};
	Drop(Level* parentLevel_, Vec3 pos, Vec3 scale_, int w_, int h_, DropType dropType_);
	void OnCollide(Body* other, float deltaTime) override;
	void OnDestroy() override;

private:
	Sprite dropSprite;
};

#endif