#pragma once
#ifndef SOLID_H
#define SOLID_H

#include "Body.h"
class Solid : public Body{
public:
	Solid() {}
	Solid(float x_, float y_, float w_, float h_);
	void OnCollide(Body* other, float deltaTime) override;
};

#endif // !SOLID_H
