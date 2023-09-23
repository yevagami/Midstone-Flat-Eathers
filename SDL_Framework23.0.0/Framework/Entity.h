#pragma once
#include "Vector.h"
#include "VMath.h"

//either the entity inherants from body, or has a body component
class Entity  {
protected:
	//position
	MATH::Vec3 pos;
	
	///Entity:
	//position
	//health
	//affiliation tag (player, enemy, NPC, other)
	//movement system
	//weapon
	//animations for sprites
	//between entity interactions

	///Body:
	//physics
	//hitboxes
	//anything scary math-y
	//textures

};

