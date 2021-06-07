#pragma once
#include <vector>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include <iostream>
//HANDLES COLLISIONS

//extension of Entity Class - done here so that Box2D include doesnt have to happen for every enemy instance
class BodiedEntity : public Entity {
private:
	b2Body* body_;
public:
	void setBody(b2Body* setTo) { body_ = setTo; }
	b2Body* getBody() { return body_; }
	b2Vec2 getPosition() { return body_->GetPosition(); }
	void LookAtPlayer(b2Vec2 playerPosition) {
		//SKELETON BILLBOARDING
		b2Vec2 lookVec_;
		lookVec_.x = playerPosition.x - body_->GetPosition().x;
		lookVec_.y = playerPosition.y - body_->GetPosition().y;
		lookVec_.Normalize();
		setforwardV(lookVec_.x, lookVec_.y);
	}
};

class CollisionWorld
{
private:
	int* score;
	int* health;
	std::vector<b2Body*> walls_;
	b2World* world_;

	std::vector<b2Body*> player_bullets;
	std::vector<b2Body*> enemy_bullets;

	//every level has a player body for that level. actual Player class is
	//in GameManager(so the data is across all levels
	b2Body * player;

	std::vector <BodiedEntity> skeleMages;
	
	void handleBulletCollisions();
public:
	void bindScore(int* binder) { score = binder; }

	CollisionWorld();
	void addWall(b2Vec2 middlePosition, b2Vec2 size);
	void update_col_world(float dt);

	//player getters
	b2Body* getPlayer() { return player; }

	void bind_hp(int* binder) { health = binder; }

	//skeleton getters and
	BodiedEntity* getSkeleMage(int at) { return &skeleMages.at(at); }
	int nrOfSkeletons() { return skeleMages.size(); }
	void spawnSkeleMage(float xPos, float yPos);

	//other collision functions
	void shootBullet(b2Vec2 position, b2Vec2 direction, bool playerBullet);
	std::vector<b2Body*>*getBullets(bool playerBullets) { if (playerBullets) { return &player_bullets; } else { return &enemy_bullets; } }
};


