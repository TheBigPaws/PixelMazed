#include "Level.h"
#include <iostream>



//world_(NULL)
Level::Level(int difficulty){
	
	difficulty_ = difficulty;

	map = Map(1);

	Ui_.get_map(map);

	ladder_up_pos = b2Vec2(map.getEntPos().at(0), map.getEntPos().at(1));
	ladder_down_pos = b2Vec2(map.getExitPos().at(0), map.getExitPos().at(1));

}

void Level::render_structures(GLuint * woodText) {
	//LADDER
	glPushMatrix();
	glTranslatef(0, 0.75f, ladder_up_pos.y + 0.5f);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	BuildingFunctions::makeBlock(ladder_up_pos.x + 0.25f, 0.0f, 0.0f, 0.1f, 2.0, 0.1f, 1, woodText);
	BuildingFunctions::makeBlock(ladder_up_pos.x + 0.75f, 0.0f, 0.0f, 0.1f, 2.0f, 0.1f, 1, woodText);
	for (int i = -2; i < 3; i++) {
		BuildingFunctions::makeBlock(ladder_up_pos.x + 0.5f, 0.1f + i * 0.3f, 0.0f, 0.4f, 0.05f, 0.05f, 5, woodText);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0f, ladder_down_pos.y + 0.5f);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	BuildingFunctions::makeBlock(ladder_down_pos.x + 0.25f, 0.0f, 0.0f, 0.1f, 0.5f, 0.1f, 1, woodText);
	BuildingFunctions::makeBlock(ladder_down_pos.x + 0.75f, 0.0f, 0.0f, 0.1f, 0.5f, 0.1f, 1, woodText);
	/*for (int i = -2; i < 3; i++) {
		BuildingFunctions::makeBlock(map.getEntPos().at(0) + 0.5f, 0.1f + i * 0.3f, 0.0f, 0.4f, 0.05f, 0.05f, 5, &woodTexture);
	}*/
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(ladder_up_pos.x, 1.5, ladder_up_pos.y);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_up_pos.x, 1.5, ladder_up_pos.y+1);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_up_pos.x+1, 1.5, ladder_up_pos.y+1);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_up_pos.x+1, 1.5, ladder_up_pos.y);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(ladder_down_pos.x, 0, ladder_down_pos.y);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_down_pos.x, 0, ladder_down_pos.y + 1);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_down_pos.x + 1, 0, ladder_down_pos.y + 1);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(ladder_down_pos.x + 1, 0, ladder_down_pos.y);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);

	for (int i = 0; i < walls.size(); i++) {
		walls.at(i).render_rect();
	}
	for (int i = 0; i < floors.size(); i++) {
		floors.at(i).render_rect();
	}
	for (int i = 0; i < chests.size(); i++) {
		glPushMatrix();
		glTranslatef(ladder_up_pos.x, 0, ladder_up_pos.y);
		chests.at(i).render();
		glPopMatrix();
	}
}

void Level::render_enemies(GLuint * skeleText) {
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int j = 0; j < collisionWorld_.nrOfSkeletons(); j++) {
		glPushMatrix();
		glTranslatef(collisionWorld_.getSkeleMage(j)->getPosition().x, 0.0f, collisionWorld_.getSkeleMage(j)->getPosition().y);
		//
		glRotatef(-collisionWorld_.getSkeleMage(j)->getRotation() * 180 / 3.14 + 90, 0.0, 1.0, 0.0);

		BuildingFunctions::makeTextRect(Vector3(-0.3, 1, 0), Vector3(-0.3, 0, 0),
			Vector3(0.3, 0, 0), Vector3(0.3, 1, 0),
			Vector3(0, 0, 1), 1.0, 1.0, skeleText);

		glPopMatrix();
	}


	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

void Level::render_bullets(GLuint * bulletText) {
	for (int i = 0; i < collisionWorld_.getBullets(true)->size(); i++) {
		b2Vec2 bul_pos = collisionWorld_.getBullets(true)->at(i)->GetPosition();
		BuildingFunctions::makeBlock(bul_pos.x, 0.6, bul_pos.y, 0.1, 0.1, 0.1, 1.0, bulletText);
	}

	for (int i = 0; i < collisionWorld_.getBullets(false)->size(); i++) {
		b2Vec2 bul_pos = collisionWorld_.getBullets(false)->at(i)->GetPosition();
		BuildingFunctions::makeBlock(bul_pos.x, 0.6, bul_pos.y, 0.1, 0.1, 0.1, 1.0, bulletText);
	}
}

void Level::render_level(GLuint* woodText, GLuint* skeleText, GLuint* bulletText) {
	

	lights_.updatePlayerLightPosition(collisionWorld_.getPlayer()->GetPosition().x, collisionWorld_.getPlayer()->GetPosition().y);
	lights_.renderLights();
	//glEnable(GL_TEXTURE_2D);
	render_structures(woodText);

	render_enemies(skeleText);

	render_bullets(bulletText);
	//glDisable(GL_TEXTURE_2D);

	//Ui_.render_UI();
}
void Level::setupLevel(GLuint* wallText, GLuint * floorText, GLuint* chestText) {

	chests.push_back(Chest(GOLD,&chestText[6], &chestText[7], &chestText[8]));

	GLuint* texture_ptr;
	//int floor_xFrom = 0;
	for (int z = 1; z < 49; z++) {
		//int floor_xFrom = -1;
		for (int x = 1; x < 49; x++) { //create all the horizontal walls first
			if (map.getTile(x, z) == WALL) {

				collisionWorld_.addWall(b2Vec2(x + 0.5, z + 0.5), b2Vec2(0.5,0.5));

				texture_ptr = &wallText[0];

				if (!(rand() % 15)) { //1 in a 15 chance for a special wall to spawn
					texture_ptr = &wallText[1 + rand() % 6];
				}

				if (map.getTile(x, z + 1) != WALL && map.getTile(x, z + 1) != UNASSIGNED) { //if there is a wall or empty, break the snip and push it
					walls.push_back(textRect(Vector3(x, 1.5f, z + 1), Vector3(x, 0, z + 1), Vector3(x + 1, 0, z + 1), Vector3(x + 1, 1.5f, z + 1), Vector3(0, 0, 1), 1, 1, texture_ptr));
				}
				if (map.getTile(x, z - 1) != WALL && map.getTile(x, z - 1) != UNASSIGNED) { //if there is a wall or empty, break the snip and push it
					walls.push_back(textRect(Vector3(x + 1, 1.5f, z), Vector3(x + 1, 0, z), Vector3(x, 0, z), Vector3(x, 1.5f, z), Vector3(0, 0, -1), 1, 1, texture_ptr));
				}
				if (map.getTile(x - 1, z) != WALL && map.getTile(x - 1, z) != UNASSIGNED) { //if there is a wall or empty, break the snip and push it
					walls.push_back(textRect(Vector3(x, 1.5f, z), Vector3(x, 0, z), Vector3(x, 0, z + 1), Vector3(x, 1.5f, z + 1), Vector3(-1, 0, 0), 1, 1, texture_ptr));
				}
				if (map.getTile(x + 1, z) != WALL && map.getTile(x + 1, z) != UNASSIGNED) { //if there is a wall or empty, break the snip and push it
					walls.push_back(textRect(Vector3(x + 1, 1.5f, z + 1), Vector3(x + 1, 0, z + 1), Vector3(x + 1, 0, z), Vector3(x + 1, 1.5f, z), Vector3(1, 0, 0), 1, 1, texture_ptr));
				}
			}
			else if (map.getTile(x, z) != UNASSIGNED) {
				texture_ptr = &floorText[0];
				if (!(rand() % 15)) { //1 in a 15 chance for a special wall to spawn
					texture_ptr = &floorText[1 + rand() % 2];
				}

				floors.push_back(textRect(Vector3(x, 0, z), Vector3(x, 0, z + 1), Vector3(x + 1, 0, z + 1), Vector3(x + 1, 0, z), Vector3(0, 1, 0), 1, 1, texture_ptr));
				floors.push_back(textRect(Vector3(x, 1.5f, z), Vector3(x, 1.5f, z + 1), Vector3(x + 1, 1.5f, z + 1), Vector3(x + 1, 1.5f, z), Vector3(0, -1, 0), 1, 1, texture_ptr));
				if (map.getTile(x, z) == LADDER_UP) {
					floors.erase(floors.begin() + (floors.size() - 1));
				}
				else if (map.getTile(x, z) == LADDER_DOWN) {
					floors.erase(floors.begin() + (floors.size() - 2));

				}
			}
		}
	}
	collisionWorld_.getPlayer()->SetTransform(b2Vec2(map.getEntPos().at(0) + 0.5, map.getEntPos().at(1) + 0.5), 0);

}

void Level::spawnSkeletons() {
	for (int i = 0; i < difficulty_ * 2; i++) {
		Room tempRoom = map.getRandomRoom();
		collisionWorld_.spawnSkeleMage(tempRoom.x + rand() % tempRoom.sizeX + 0.5, tempRoom.y + rand() % tempRoom.sizeY + 0.5);
	}
}


void Level::update_level(float dt) {

	Ui_.updateMiniMapProgress(collisionWorld_.getPlayer()->GetPosition().x, collisionWorld_.getPlayer()->GetPosition().y);

	collisionWorld_.update_col_world(dt);

	int canSeePlayer = 0;
	lights_.setEnemyLight(0, 0, 0);//reset for if there are no lights to render

	//sets lights for skeletons and billboarding
	for (int i = 0; i < collisionWorld_.nrOfSkeletons(); i++) {
		if (map.canSee(collisionWorld_.getSkeleMage(i)->getPosition().x, collisionWorld_.getSkeleMage(i)->getPosition().y,
					   collisionWorld_.getPlayer()->GetPosition().x, collisionWorld_.getPlayer()->GetPosition().y)) {

			
			canSeePlayer++;
			lights_.setEnemyLight(collisionWorld_.getSkeleMage(i)->getPosition().x, collisionWorld_.getSkeleMage(i)->getPosition().y, canSeePlayer);
			collisionWorld_.getSkeleMage(i)->LookAtPlayer(collisionWorld_.getPlayer()->GetPosition());
			
			//shooting
			collisionWorld_.getSkeleMage(i)->incrementCoolDown(dt);
			if (collisionWorld_.getSkeleMage(i)->canShoot()) {
				collisionWorld_.shootBullet(collisionWorld_.getSkeleMage(i)->getPosition(), b2Vec2(collisionWorld_.getSkeleMage(i)->getforwardV()[0], collisionWorld_.getSkeleMage(i)->getforwardV()[1]), false);
				collisionWorld_.getSkeleMage(i)->resetCD();
			}
		}
	}
}

