#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <functional>
#include "Body.h"

class Level;
class Trigger : public Body{
public:
	Trigger(){}
	Trigger(Level* parentScene_, Vec3 pos_, int w_, int h_, std::function<void()> callback_);

	void OnCollide(Body* other, float deltaTime) override {
		if (other->type == PLAYER) {
			callback();
		}
	}

	void OnDestroy() override {
		triggerSprite.onDestroy();
		delete hitbox;
		cutout = nullptr;
		parentLevel = nullptr;
	}

	std::function<void()> callback;

private:
	Sprite triggerSprite;
};

#endif // ! TRIGGER_H

