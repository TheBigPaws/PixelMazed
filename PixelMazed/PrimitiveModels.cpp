#include "PrimitiveModels.h"

Chest::Chest(Type Type, GLuint * frontTXT, GLuint * sideTXT, GLuint * topbotTXT) {
	type_ = Type;

	//front top
	chestTexture[0] = new textRect(Vector3(-0.3, 0.6, 0.3), Vector3(-0.3, 0.4, 0.3), Vector3(0.3, 0.4, 0.3), Vector3(0.3, 0.6, 0.3), Vector3(0.0, 0.0, 1.0), 1.0, 0.33, frontTXT);
	//front bottom
	chestTexture[1] = new textRect(Vector3(-0.3, 0.4, 0.3), Vector3(-0.3, 0.0, 0.3), Vector3(0.3, 0.0, 0.3), Vector3(0.3, 0.4, 0.3), Vector3(0.0, 0.0, 1.0), 1.0, -0.66, frontTXT);

	//right top
	chestTexture[2] = new textRect(Vector3(0.3, 0.6, 0.3), Vector3(0.3, 0.4, 0.3), Vector3(0.3, 0.4, -0.3), Vector3(0.3, 0.6, -0.3), Vector3(1.0, 0.0, 0.0), 1.0, 0.33, sideTXT);
	//right bottom
	chestTexture[3] = new textRect(Vector3(0.3, 0.4, 0.3), Vector3(0.3, 0.0, 0.3), Vector3(0.3, 0.0, -0.3), Vector3(0.3, 0.4, -0.3), Vector3(1.0, 0.0, 0.0), 1.0, -0.66, sideTXT);

	//left top
	chestTexture[4] = new textRect(Vector3(-0.3, 0.6, 0.3), Vector3(-0.3, 0.4, 0.3), Vector3(-0.3, 0.4, -0.3), Vector3(-0.3, 0.6, -0.3), Vector3(-1.0, 0.0, 0.0), 1.0, 0.33, sideTXT);
	//left bottom
	chestTexture[5] = new textRect(Vector3(-0.3, 0.4, 0.3), Vector3(-0.3, 0.0, 0.3), Vector3(-0.3, 0.0, -0.3), Vector3(0-.3, 0.4, -0.3), Vector3(-1.0, 0.0, 0.0), 1.0, -0.66, sideTXT);
	
	//back top
	chestTexture[6] = new textRect(Vector3(-0.3, 0.6, -0.3), Vector3(-0.3, 0.4, -0.3), Vector3(0.3, 0.4, -0.3), Vector3(0.3, 0.6, -0.3), Vector3(0.0, 0.0, -1.0), 1.0, 0.33, sideTXT);
	//back bottom
	chestTexture[7] = new textRect(Vector3(-0.3, 0.4, -0.3), Vector3(-0.3, 0.0, -0.3), Vector3(0.3, 0.0, -0.3), Vector3(0.3, 0.4, -0.3), Vector3(0.0, 0.0, -1.0), 1.0, -0.66, sideTXT);

	//lid
	chestTexture[8] = new textRect(Vector3(-0.3, 0.6, -0.3), Vector3(-0.3, 0.6, 0.3), Vector3(0.3, 0.6, 0.3), Vector3(0.3, 0.6, -0.3), Vector3(0.0, 1.0, 0.0), 1.0, 1.0, topbotTXT);
	//bottom
	chestTexture[9] = new textRect(Vector3(-0.3, 0.01, -0.3), Vector3(-0.3, 0.01, 0.3), Vector3(0.3, 0.01, 0.3), Vector3(0.3, 0.01, -0.3), Vector3(0.0, -1.0, 0.0), 1.0, 1.0, topbotTXT);

}