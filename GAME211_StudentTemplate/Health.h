#pragma once
class Health {

protected:
	int health;
	int maxHealth;
public:

	void takeDamage(int damage) {
		health =- damage;
	}

	void setHealthToMax() {
		health = maxHealth;
	}

	void setHealth(int newHealth) {
		health = newHealth;
	}

};

