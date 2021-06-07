#pragma once
#include "BuildingFunctions.h"
#include "Map.h"
//#include "Camera.h"
#include "CollisionWorld.h"
#include "Lights.h"
#include "UI.h"
#include "PrimitiveModels.h"

class Level
{
private:

	b2Vec2 ladder_down_pos, ladder_up_pos;
	int difficulty_;

	UI Ui_;

	Map map;
	
	std::vector<textRect> walls;
	std::vector<textRect> floors;
	std::vector<Chest> chests;

	CollisionWorld collisionWorld_;

	Lights lights_;
protected:
	void render_structures(GLuint* woodText);
	void render_enemies(GLuint* skeleText);
	void render_bullets(GLuint* bulletText);
public:
	Level(int difficulty);

	UI* getUI() { return &Ui_; }

	void bindScoreToCol(int* binder) { collisionWorld_.bindScore(binder); Ui_.score_ = binder; }

	void setupLevel(GLuint* wallText, GLuint* floorText, GLuint* chestText);

	void update_level(float dt);
	void render_level(GLuint* woodText, GLuint* skeleText, GLuint* bulletText);

	void spawnSkeletons();

	b2Body * get_player_body_LEVELLOCAL() { return collisionWorld_.getPlayer(); }
	b2Vec2 ladder_down_Getpos() { return ladder_down_pos; }
	b2Vec2 ladder_up_Getpos() { return ladder_up_pos; }
	
	void shootBullett(b2Vec2 position, b2Vec2 direction, bool playerBullet) {
		collisionWorld_.shootBullet(position, direction, playerBullet);
	}
	void BindPlayerHP(int* binder) { Ui_.bindHP(binder); collisionWorld_.bind_hp(binder); }
};

