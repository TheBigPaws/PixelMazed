#include "CollisionWorld.h"

//collisionWorld constructor. Some initializations
CollisionWorld::CollisionWorld() :
	world_(NULL),
	walls_(NULL)
{
	world_ = new b2World(b2Vec2(0.0f, 0.0f));




	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(600, 600);
	player = world_->CreateBody(&bodyDef);


	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.2f, 0.2f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;



	player->CreateFixture(&fixtureDef);	
}

//function to create a wall at on a set position and size
void CollisionWorld::addWall(b2Vec2 middlePosition, b2Vec2 size) {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(middlePosition.x, middlePosition.y);
	walls_.push_back(world_->CreateBody(&groundBodyDef));
	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x,size.y);
	walls_.back()->CreateFixture(&groundBox, 0.0f);

}

//update function for the collisionn= woi=rld based on deltaTime
void CollisionWorld::update_col_world(float dt) {
	world_->Step(dt, 6, 2);
	
	for (int i = 0; i < player_bullets.size(); i++) {

		for (b2ContactEdge * contact = player_bullets.at(i)->GetContactList(); contact != 0; contact = contact->next) {
			for (int j = 0; j < skeleMages.size(); j++) {
				if (contact->contact->GetFixtureA() == skeleMages.at(j).getBody()->GetFixtureList() || contact->contact->GetFixtureB() == skeleMages.at(j).getBody()->GetFixtureList()) {
					player_bullets.erase(player_bullets.begin() + i);
					skeleMages.at(j).takeDamage(25);
					if (!skeleMages.at(j).getAlive()) {
						skeleMages.erase(skeleMages.begin() + j);
						*score += 10;
					}
					return;
				}
			}
		}
	}
	
	for (int i = 0; i < enemy_bullets.size(); i++) {

		for (b2ContactEdge* contact = enemy_bullets.at(i)->GetContactList(); contact != 0; contact = contact->next) {
			if (contact->contact->GetFixtureA() == player->GetFixtureList() || contact->contact->GetFixtureB() == player->GetFixtureList()) {
				enemy_bullets.erase(enemy_bullets.begin() + i);
				*health -= 50;
				if (health<0) {
					//GAME OVER
				}
				return;
			}
		}
	}
}

//spawns a skeleton on a set position
void CollisionWorld::spawnSkeleMage(float xPos, float yPos) {

	BodiedEntity tempSkM;
	tempSkM.setName(SKELEMAGE);
	tempSkM.setAS(3.5);
	tempSkM.setHealth(100);
	skeleMages.push_back(tempSkM);//create and push a skeleton

	b2BodyDef skelebd; //create the body for it
	skelebd.type = b2_dynamicBody;
	skelebd.fixedRotation = true;
	skelebd.position.Set(xPos, yPos);

	skeleMages.back().setBody(world_->CreateBody(&skelebd)); //add the body to the skeleton

	b2PolygonShape dynamicBox_sk; //create fixture
	dynamicBox_sk.SetAsBox(0.2f, 0.2f);
	b2FixtureDef fixtureDef_sk;
	fixtureDef_sk.shape = &dynamicBox_sk;
	fixtureDef_sk.density = 1.0f;
	//fixtureDef_sk.friction = 0.3f;

	skeleMages.back().getBody()->CreateFixture(&fixtureDef_sk); //set the fixture
}


void CollisionWorld::shootBullet(b2Vec2 position, b2Vec2 direction, bool playerBullet) {

	b2BodyDef bulletBody; //create the body for it
	bulletBody.type = b2_dynamicBody;
	bulletBody.fixedRotation = true;
	bulletBody.position = position + direction;

	if (playerBullet) {
		player_bullets.push_back(world_->CreateBody(&bulletBody));
		if (player_bullets.size() > 10) { //cap at 10 bullets to avoid performance issues
			player_bullets.erase(player_bullets.begin());
		}
	}
	else {
		enemy_bullets.push_back(world_->CreateBody(&bulletBody));
		if (enemy_bullets.size() > 10) {
			enemy_bullets.erase(enemy_bullets.begin());//cap at 10 bullets to avoid performance issues

		}
	}

	b2PolygonShape dynamicBox_bl; //create fixture
	dynamicBox_bl.SetAsBox(0.05f, 0.05f);
	b2FixtureDef fixtureDef_bl;
	fixtureDef_bl.shape = &dynamicBox_bl;
	fixtureDef_bl.density = 1.0f;

	b2Vec2 direction_ = b2Vec2(direction.x / 20, direction.y / 20 );

	if (playerBullet) {
		player_bullets.back()->CreateFixture(&fixtureDef_bl);
		player_bullets.back()->ApplyLinearImpulse(direction_, b2Vec2(0, 0), true);
	}
	else {
		enemy_bullets.back()->CreateFixture(&fixtureDef_bl);
		enemy_bullets.back()->ApplyLinearImpulse(direction_, b2Vec2(0, 0), true);

	}



}