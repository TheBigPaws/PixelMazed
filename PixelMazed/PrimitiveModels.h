#pragma once
#include "BuildingFunctions.h"

enum Type {GOLD,SILVER,BRONZE};
class Chest : public BuildingFunctions
{
private:
	Type type_;
	float top_rotation;
	float top_rotationMove;
	textRect * chestTexture[10] = { nullptr };
public:
//chests sides are declared in this order front, right, left, back, up, down. always both quads get done for tht at side
	Chest(Type Type,GLuint * frontTXT, GLuint * sideTXT, GLuint * topbotTXT);
	void render() {
		for (int i = 0; i < 10; i++) {
			chestTexture[i]->render_rect();
			
		}
	}
};

