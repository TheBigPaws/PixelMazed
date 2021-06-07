#pragma once
#include <stack>
enum Name{SKELEMAGE, PLAYER};
enum AggroState{InCombat,};
class Entity
{
protected:
	Name name;
	bool alive = true;
	int health, wisdom, stamina, strength,level;
	float speed;
	float forwardV[2];
	float Xrotation;

	float attackSpeed = 1.5;
	float coolDown = 1.5;

	//std::stack<int*> walkPath;
public:
	void takeDamage(int dmg) {
		health -= dmg;
		if (health < 0) { alive = false; }
	}

	void resetCD() { coolDown = attackSpeed; }
	void incrementCoolDown(float dt) {
		coolDown -= dt;
	}
	void setAS(float Attack_s) { attackSpeed = Attack_s; }
	//increments deltaTime to cooldown and returns whether the enemy is ready to attack
	bool canShoot() {
		
		if (coolDown < 0) {
			return true;
		}
		else { return false; }
	}

	// to be overwritten
	//virtual void attack();
	bool getAlive() { return alive; }
	float * getforwardV() { return forwardV; }
	void setforwardV(float x, float y);
	float getRotation() { return Xrotation; }
	void setHealth(int hp) { health = hp; }
	int * getHealth() { return &health; }
	Name getName() { return name; }
	void setName(Name name_) { name = name_; }
};

