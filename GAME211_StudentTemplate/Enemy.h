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
	//Enemy type definitions
	enum subType {
		flash = 0, 
		miracle = 1, 
		strong = 2
	};
	
	//constructors
	Enemy(Level* parentLevel_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_) :
		Body(parentLevel_, pos_, scale_, w_, h_, image_) {
		type = ENEMY;
	}
	Enemy(Level* parentLevel_, Vec3 pos_, subType type_);

	//methods
	void Update(float time) override;
	void OnCollide(Body* other, float deltaTime) override;
	void OnDestroy() override;
	void takeDamage(float amount) override;

private:
	//enemy states
	enum states { idle, walk, followPlayer };
	states currentState = followPlayer;

	//Enemy specific variables
	float enemyMoveSpeed;
	float enemyPower;
	Body* playerReference = nullptr;

	//Map contain multiple enemy definitions
	std::unordered_map<subType, enemyVariables> enemyDefintions{
		{subType::flash, enemyVariables{
			250.0f,
			100.0f,
			IMG_Load("Textures/programmer_art/enemy.png"),
			35.0f,
			128.0f,
			128.0f
		}},

		{subType::miracle, enemyVariables{
			175.0f,
			1500.0f,
			IMG_Load("Textures/programmer_art/enemy.png"),
			20.0f,
			128.0f,
			128.0f
		}},

		{subType::strong, enemyVariables{
			500.0f,
			750.0f,
			IMG_Load("Textures/programmer_art/enemy.png"),
			50.0f,
			128.0f,
			128.0f
		}},

	};

	//state methods
	void state_idle();
	void state_walk();
	void state_followPlayer();
};

