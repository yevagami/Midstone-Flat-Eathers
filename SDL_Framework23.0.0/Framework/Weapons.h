#pragma once
#include <iostream>
#include <string>


///	Weapons Parent Class
//	needs collision


class Weapon {
protected:
	/// Variables | Attributes
	//	weapon's name
	std::string name;
	//	amount of damage dealt
	int damage;
	//	range of the weapon
	int range;

public:

	// Constructor: create a new 'weapon' with the provided name, dmg, and range
	Weapon(std::string weaponName, int damage, int range) : 
		name(weaponName), 
		damage(damage), 
		range(range) 
	{ }

	// Constructor: create a new 'weapon' with default name, dmg, and range
	Weapon() {
		name = "winston";
		damage = 0;
		range = 0;
	}

	virtual ~Weapon() { };

	virtual std::string getName() const { return name; }
	virtual void setName(const char* newName) { name = newName; }
	
	virtual int getDamage() const { return damage; }
	virtual void setDamage(int newDamage){ damage = newDamage; }
	
	virtual int getRange() const { return range; }
	virtual void setRange(int newRange){ range = newRange; }

	virtual void attack();
};


///	Melee Weapons


class Melee : public Weapon {
protected:
	float sharpness;
	int swingSpeed;
	int staminaCost;

public:
	//name, damage, range, sharpness(0-1), swing speed, stamina cost(max stamina could be 100)
	Melee(std::string weaponName, int damage, int range, int sharpness, int swingSpeed, int staminaCost) :
		Weapon(weaponName, damage, range),
		sharpness(sharpness),
		swingSpeed(swingSpeed),
		staminaCost(staminaCost)
	{ };

	Melee() {
		name = "reinhardt";
		damage = 0;
		range = 0;
		sharpness = 0.0f;
		swingSpeed = 0;
		staminaCost = 0;
	}

	~Melee() {}

	int getSharpness() const { return sharpness; }
	void setSharpness(float newSharpness){ sharpness = newSharpness; }
	int getSwingSpeed() const {	return swingSpeed; }
	void setSwingSpeed(int newSwingSpeed) { swingSpeed = newSwingSpeed; }
	int getStaminaCost() const { return staminaCost; }
	int getDamage() {	
		float damageModifier = sharpness + 1; //	sharpness should always be between 0 and 1 (or close to that)
		return damage * damageModifier;
		}

	void attack() override {
		bool
			swingCon = true;

		if (swingCon) {
			swing();
		} else {
			std::cout << "n\n";
		}
	}

	void swing() {
		staminaCost = 25;
		getDamage();
	}

	void slash() {
		staminaCost = 15;
		getDamage();
	}

	void stab() {
		staminaCost = 10;
		getDamage();
	}
};

///	Ranged Weapons

class Ranged : public Weapon {
protected:
	int ammo;
	int reloadTime;
	
public:
	
	Ranged(std::string weaponName, int damage, int range, int ammo, int reloadTime) : 
		Weapon(weaponName, damage, range), 
		ammo(ammo), 
		reloadTime(reloadTime) 
	{ };

	Ranged() {
		name = "joey gunceffa";
		damage = 0;
		range = 0;
		ammo = 0;
		reloadTime = 0;
	}

	~Ranged() {}

	int getAmmo() const { return ammo; }
	int getReloadTime() const {	return reloadTime; }

	void attack() override;

	void reload();
};

///	Shields

class Shield : public Weapon {
protected:
	int durability; //	100
	int maxDurability; // 100
	float blockChance;
	int blockPower;

public:

	Shield(std::string weaponName, int damage, int range, int durability, int maxDurability, float blockChance, int blockPower) :
		Weapon(weaponName, damage, range),
		durability(durability),
		maxDurability(maxDurability),
		blockChance(blockChance),
		blockPower(blockPower) 
	{ };

	Shield() {
		name = "brigitte";
		damage = 0;
		range = 0;
		durability = 0;
		maxDurability = 0;
		blockChance = 0;
		blockPower = 0;
	}

	~Shield() {}

	int getDurability() const { return durability; }
	int getMaxDurability() const { return maxDurability; }
	float getBlockChance() const { return blockChance; }
	int getBlockPower() const { return blockPower; }

	//TO DO
	void attack() override;

	//	returns how much damage is blocked by the current shield
	int getDamage(int incomingDamage) {
		//to do: add blocking logic
		bool doesBlock = true;

		if (doesBlock) {
			return incomingDamage * blockPower;
		} else {
			return incomingDamage;
		}


	};

	void bash();

	void damageAura();

	void repair() { durability = maxDurability; };
};