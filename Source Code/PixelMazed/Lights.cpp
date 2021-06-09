#include "Lights.h"

void Lights::renderLights() {

	glLightfv(GL_LIGHT1, GL_DIFFUSE, player_Light_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, player_Light_Position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);

	

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient_Light_Diffuse);
	//GL_LIGHT

	//render  light for enemies
	for (int i = 1; i <= enemiesLit; i++) {
		glLightfv(GL_LIGHT1 + i, GL_DIFFUSE, enemy_Light_Diffuse);
		glLightfv(GL_LIGHT1 + i, GL_POSITION, enemy_Light_Position[i-1]);

		glLightf(GL_LIGHT1 + i, GL_CONSTANT_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1 + i, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT1 + i, GL_QUADRATIC_ATTENUATION, 0.1);
	}
}

void Lights::setEnemyLight(float positionX, float positionY, int lightsToInitiate) {

	if (lightsToInitiate <= 6) {
		enemiesLit = lightsToInitiate;
		if (lightsToInitiate) {
			enemy_Light_Position[lightsToInitiate - 1][0] = positionX;
			enemy_Light_Position[lightsToInitiate - 1][1] = 0.75;
			enemy_Light_Position[lightsToInitiate - 1][2] = positionY;
			enemy_Light_Position[lightsToInitiate - 1][3] = 1.0;
		}
	}
}
