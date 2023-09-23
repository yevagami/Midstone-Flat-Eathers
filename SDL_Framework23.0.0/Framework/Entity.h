#pragma once
#include "Vector.h"
#include <vector>
#include "VMath.h"
#include "Weapons.h"
#include "Body.h"


//	not the enum struct
//	reason for being outside the character class is cuz if its outside its easier to make factions of entities. we could use that for bosses (the boss spawns a faction of enemies)
enum struct Affiliation { 
	Undefined, 
	Entity, 
	Player, 
	Enemy, 
	NPC,
	Debug
};

//	for the futureeeee oOoOOoooOo (examples, idk if this will even stay)
enum struct Faction { 
	Undefined,
	Enemies, 
	NPCs, 
	Debug
};

enum struct StatusType {
	None,
	Poisoned,
	Paralyzed,
	Debug
};


class Entity {
public: 
	Entity();
	Entity(const Vec3& initialPosition);
	Entity(const Vec3& initialPosition, float initialHealth);
	Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon);

	Entity(const Vec3& initialPosition, Affiliation initialAffiliation);
	Entity(const Vec3& initialPosition, float initialHealthAffiliation, Affiliation initialAffiliation);
	Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, Affiliation initialAffiliation);



	void ApplyForce(const Vec3& force);
	void Update(float deltaTime);

	void entityController(const SDL_Event& events);


#pragma region gettes and setters
public:
	virtual void takeDamage(float damage);

	void heal(float health);
	float getHealth();
	float getMaxHealth();
	void setMaxHealth(float newMaxHealth);
	float getDefaultHealth();
	void setDefaultHealth(float newDefaultHealth);
	void equipWeapon(Weapon newWeapon);

	Affiliation getTag();
	void setTag(Affiliation newAffiliation);
	Faction getFaction();
	void setFaction(Faction newFaction);

#pragma endregion

protected:
	//	health, status effect, equipped weapon
	Character self;
	//	affiliation tag
	Affiliation tag;
	//	faction group
	Faction group;
	//	physics body | pos, vel, accel, forces, math
	Body body;
};


//	handles uniqueness
struct Character {
	//	health
	float currentHealth;
	float defaultHealth;
	float maxHealth;

	//	status effects | might not end up using
	std::vector<StatusEffect> activeStatusEffects;

	//	weapon
	Weapon equippedWeapon;

};


struct StatusEffect {
	StatusType type;
	float duration;

	//	effect constwuctor >-<
	StatusEffect(StatusType statusType, float effectDuration) : type(statusType), duration(effectDuration) {}

};


#pragma region plans and such
///Entity:
//	sprites
//	animations for sprites

///Body:
//	physics
//	hitboxes
//	anything scary math-y


///	TEXTURES IN THE ENTITY OR THE BODY CLASS?
#pragma endregion