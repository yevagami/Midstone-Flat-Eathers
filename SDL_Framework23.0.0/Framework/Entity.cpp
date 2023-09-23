#include "Entity.h"
#include "ConsistentConsole.h"
ConsistentConsole ccEntity;

#pragma region Constructors
Entity::Entity() {
	body.pos = Vec3(0, 0, 0);

	self.currentHealth = self.defaultHealth;

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition) {
	body.pos = initialPosition;

	self.currentHealth = self.defaultHealth;

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition, float initialHealth) {
	body.pos = initialPosition;
	self.currentHealth = initialHealth;

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon) {
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	self.equippedWeapon = initialWeapon;

	tag = Affiliation::Undefined;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition, Affiliation initialAffiliation) {
	body.pos = initialPosition;
	self.currentHealth = self.defaultHealth;

	tag = initialAffiliation;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition, float initialHealth, Affiliation initialAffiliation) {
	body.pos = initialPosition;
	self.currentHealth = initialHealth;

	tag = initialAffiliation;
	group = Faction::Undefined;
}

Entity::Entity(const Vec3& initialPosition, float initialHealth, Weapon initialWeapon, Affiliation initialAffiliation) {
	body.pos = initialPosition;
	self.currentHealth = initialHealth;
	self.equippedWeapon = initialWeapon;

	tag = initialAffiliation;
	group = Faction::Undefined;
}
#pragma endregion

#pragma region Getters n Setters
float Entity::getHealth() {
	return self.currentHealth;
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


void Entity::heal(float health) {
	bool canHeal = self.currentHealth <= self.maxHealth;
	if (canHeal) {
		self.currentHealth += health; 
	} else {
		ccEntity.consoleManager("error", "cannot heal entity, they're already at max health"); 
	}
}