#pragma once
#include <functional>

#include "Body.h"
#include "Drop.h"
#include <unordered_map>

//This struct is merely for the enemy subtype map
struct enemyVariables {
	float health;
	float moveSpeed;
	std::string imagePath;
	float power;
	float w;
	float h;
};

class PlayerBody;
class Enemy : public Body{
public:
	//Enemy type definitions
	enum subType {
		flash = 0, 
		miracle = 1, 
		strong = 2,
		mybike = 3
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

	void SetOnDeath(const std::function<void()>& onDeath_);
	void SetOnHurt(const std::function<void()>& onOuchie_);

private:
	//enemy states
	enum states { idle, walk, followPlayer };
	states currentState = followPlayer;
	std::function<void()> OnDeath;
	std::function<void()> OnHurt;

	//Enemy specific variables
	float enemyMoveSpeed;
	float enemyPower;
	float maxDrops = 3;
	PlayerBody* playerReference = nullptr;
	float enemyChaseDistance = 500.0f;

	float enemyHitboxW = 98.0f;
	float enemyHitboxH = 128.0f;
	//Map contain multiple enemy definitions
	std::unordered_map<subType, enemyVariables> enemyDefintions{
		{subType::flash, enemyVariables{
			225.0f,
			150.0f,
			"Textures/programmer_art/enemyangy.png",
			35.0f,
			enemyHitboxW,
			enemyHitboxH
		}},

		{subType::miracle, enemyVariables{
			75.0f,
			300.0f,
			"Textures/programmer_art/enemyuwu.png",
			10.0f,
			enemyHitboxW,
			enemyHitboxH
		}},

		{subType::strong, enemyVariables{
			350.0f,
			50.0f,
			"Textures/programmer_art/enemyadriel.png",
			86.25f,
			enemyHitboxW,
			enemyHitboxH
		}},

		{subType::mybike, enemyVariables{
			350.0f,
			250.0f,
			"Textures/programmer_art/enemymybike.png",
			25.0f,
			enemyHitboxW,
			enemyHitboxH
		}},

	};

	//state methods
	void state_idle();
	void state_walk();
	void state_followPlayer();

	//Spawn drops when the enemy dies
	void SpawnDrops();
};

