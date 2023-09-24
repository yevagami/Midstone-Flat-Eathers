#include "Entity.h"
#include "ConsistentConsole.h"
ConsistentConsole ccEntity;

#pragma region Constructors
Entity::Entity() {
	self.name = "defaultName";
	textureFile = "";
	body.pos = Vec3(0, 0, 0);
	self.currentHealth = self.defaultHealth;
	//	no weapon

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition) {
	self.name = entityName;
	textureFile = "";
	body.pos = initialPosition;
	self.currentHealth = self.defaultHealth;
	//	no weapon

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = self.defaultHealth;
	//	no weapon

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	//	no weapon

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	self.equippedWeapon = initialWeapon;

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, Affiliation initialAffiliation, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = self.defaultHealth;
	//	no weapon

	tag = initialAffiliation;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, Affiliation initialAffiliation, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	//	no weapon

	tag = initialAffiliation;
	group = Faction::Undefined;
}

Entity::Entity(const char* entityName, const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, Affiliation initialAffiliation, const char* textureFile_) {
	self.name = entityName;
	textureFile = textureFile_;
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	self.equippedWeapon = initialWeapon;

	tag = initialAffiliation;
	group = Faction::Undefined;
}
#pragma endregion

#pragma region Getters n Setters
float Entity::getCurrentHealth() {
	return self.currentHealth;
}

void Entity::setCurrentHealth(float newHealth) {
	if (newHealth <= self.maxHealth) {
		self.currentHealth = newHealth;
	} else {
		ccEntity.consoleManager("error", "cannot set entity health, ur health healths too hard");
	}
}

void Entity::addToCurrentHealth(float healthToAdd) {
	if (healthToAdd <= self.maxHealth) {
		self.currentHealth += healthToAdd;
	} else {
		ccEntity.consoleManager("error", "cannot add to entity health, thats rough");
	}
	

}

float Entity::getMaxHealth() {
	return self.maxHealth;
}

void Entity::setMaxHealth(float newMaxHealth) {
	self.maxHealth = newMaxHealth;
}

float Entity::getDefaultHealth() {
	return self.defaultHealth;
}

void Entity::setDefaultHealth(float newDefaultHealth) {
	self.defaultHealth = newDefaultHealth;
}

void Entity::equipWeapon(Weapon newWeapon) {
	self.equippedWeapon = newWeapon;
}

Affiliation Entity::getTag() {
	return tag;
}

void Entity::setTag(Affiliation newAffiliation) {
	tag = newAffiliation;
}

Faction Entity::getFaction() {
	return group;
}

void Entity::setFaction(Faction newFaction) {
	group = newFaction;
}
#pragma endregion


void Entity::ApplyForce(const Vec3& force) {


}


void Entity::Update(float deltaTime) {


}

void Entity::takeDamage(float damage) {
	self.currentHealth -= damage;
}