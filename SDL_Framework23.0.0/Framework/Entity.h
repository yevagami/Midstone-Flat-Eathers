#pragma once
#include "Vector.h"
#include <vector>
#include "VMath.h"
#include "Weapons.h"
#include "Body.h"


//	top 500 enum structs
//	Affiliationns/Tags are labels to give each spawned entity
enum struct Affiliation { 
	Undefined, 
	Entity, 
	Player, 
	Enemy, 
	NPC,
	Debug
};

//	Factions are formed by groups of entities in special situations (boss fights)
enum struct Faction { 
	Undefined,
	Enemies, 
	NPCs, 
	Debug
};

//	Status effects go here:
enum struct StatusType {
	None,
	Poisoned,
	Paralyzed,
	Debug
};


class Entity {
public: 
	//	Constructors:
	Entity();
	Entity(const Vec3& initialPosition);
	Entity(const Vec3& initialPosition, float initialHealth);
	Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon);

	Entity(const Vec3& initialPosition, Affiliation initialAffiliation);
	Entity(const Vec3& initialPosition, float initialHealthAffiliation, Affiliation initialAffiliation);
	Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, Affiliation initialAffiliation);
	
	//	Apply force
	void ApplyForce(const Vec3& force);
	//	Update
	void Update(float deltaTime);
	//	Entity event handler
	void entityController(const SDL_Event& events);
	
	
	///	to-do:
	
	//	sprites
	
	//	hitboxes
	
	//	collisions
	
	//	death and despawn
	
	//	destructor
	
	//	then change the current constructors to support sprites
	


#pragma region gettes and setters
public:
	//	calculates how much damage should be taken
	virtual void takeDamage(float damage);

	//	heal by the provided float
	void heal(float health);
	//	return the current health
	float getHealth();
	//	return the max health
	float getMaxHealth();
	//	set a new max health
	void setMaxHealth(float newMaxHealth);
	//	return the default health
	float getDefaultHealth();
	//	set a new default health
	void setDefaultHealth(float newDefaultHealth);
	//	equip the provided weapon
	void equipWeapon(Weapon newWeapon);
	//	return the current entity's tag
	Affiliation getTag();
	//	set a new tag
	void setTag(Affiliation newAffiliation);
	//	return the current entity's faction
	Faction getFaction();
	//	set a new faction
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