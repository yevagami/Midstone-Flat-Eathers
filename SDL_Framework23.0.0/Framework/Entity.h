#pragma once
#include "Vector.h"
#include "FileManager.h"
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
protected:
	//	Texture stuff
	SDL_Texture* texture = nullptr;
	const char* textureFile = "";

public:
	//	Texture methods
	SDL_Texture* GetTexture() { return texture; }
	void SetTexture(SDL_Texture* texture_) { texture = texture_; }

	const char* GetTextureFile() { return textureFile; };
	void SetTextureFile(const char* textureFile_) { textureFile = textureFile_;	};

public:

	//	Constructors:
	Entity();
	Entity(const char* entityName, const Vec3& initialPosition);
	Entity(const char* entityName, const Vec3& initialPosition, const char* textureFile__);
	Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, const char* textureFile_);
	Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, const char* textureFile_);

	Entity(const char* entityName, const Vec3& initialPosition, Affiliation initialAffiliation, const char* textureFile_);
	Entity(const char* entityName, const Vec3& initialPosition, float initialHealthAffiliation, Affiliation initialAffiliation, const char* textureFile_);
	Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, Affiliation initialAffiliation, const char* textureFile_);
	
	//	SDL Methods
	void onCreate();
	//	Apply force
	void ApplyForce(const Vec3& force);
	//	Update
	virtual void Update(float deltaTime);
	//	Entity event handler
	void EntityController(const SDL_Event& events);
	//	Render
	void Render();
	//	On Destroy
	void onDestroy();
		


	///	to-do:
	
		//	hitboxes
		bool generateHitboxFromSprite();
		bool makeHitbox();
		//	collisions
		//	spawning, death and despawn
		//	destructor
		//	then change the current constructors to support sprites
		//	movement
	


#pragma region gettes and setters
public:
	//	calculates how much damage should be taken
	virtual void takeDamage(float damage);
	//	heal by the provided float
	void setCurrentHealth(float newHealth);
	//	adds the provided float to the health
	void addToCurrentHealth(float healthToAdd);
	//	return the current health
	float getCurrentHealth();
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
	//	Basic Movement
	Transform move;
	//	affiliation tag
	Affiliation tag;
	//	faction group
	Faction group;
	//	physics body | pos, vel, accel, forces, math
	Body body;
};


//	handles uniqueness
struct Character {
	//	name
	const char* name;

	//	health
	float currentHealth;
	float defaultHealth;
	float maxHealth;

	//	status effects | might not end up using
	std::vector<StatusEffect> activeStatusEffects;

	//	weapon
	Weapon equippedWeapon;

	Character() {
		maxHealth = 100;
		defaultHealth = maxHealth;
		currentHealth = defaultHealth;
	};
};

struct Transform {
	//int x, y;
	//is moving done here? or in the body..?
	//also is position here, or in the body?
};

struct StatusEffect {
	StatusType type;
	float duration;

	//	effect constwuctor >-<
	StatusEffect(StatusType statusType, float effectDuration) : type(statusType), duration(effectDuration) 
	{}
};