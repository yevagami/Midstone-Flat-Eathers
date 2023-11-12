#pragma once
#include "Body.h"
#include <unordered_map>

struct enemyVariables {
	float health;
	float moveSpeed;
	SDL_Surface* image;
	float power;
	float w;
	float h;
};

class Enemy : public Body{
public:
	//States
	enum states { idle, walk, followPlayer };
	states currentState = followPlayer;

	//Enemy type definitions
	enum subType {
		flash = 0, 
		miracle = 1, 
		strong = 2
	};

	std::unordered_map<subType, enemyVariables> enemyDefintions{
		{subType::flash, enemyVariables{
			100.0f,
			900.0f,
			IMG_Load("Textures/programmer_art/enemy.png"),
			0.0f,
			128.0f,
			128.0f
		}},

		{subType::miracle, enemyVariables{
			75.0f,
			1500.0f,
			nullptr,
			0.0f,
			128.0f,
			128.0f
		}},

		{subType::strong, enemyVariables{
			250.0f,
			750.0f,
			nullptr,
			0.0f,
			128.0f,
			128.0f
		}},

	};
	
	//Enemy specific variables
	float moveSpeed;
	float power; 
	Body* player = nullptr;

	//constructors
	Enemy(Level* parentLevel_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_) :
		Body(parentLevel_, pos_, scale_, w_, h_, image_) {
		type = ENEMY;
	}
	Enemy(Level* parentLevel_, Vec3 pos_, subType type_);


};

