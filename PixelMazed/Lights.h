#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include "time.h"
// Further includes should go here:
#include "SOIL.h"
#include "Vector3.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
class Lights
{
private:
	GLfloat ambient_Light_Diffuse[4] = { 0.0f,0.0f,0.0f, 1.0f };
	GLfloat ambient_Light_Ambient[4] = { 0.2f, 0.2f, 0.2f, 1.2f };
	GLfloat player_Light_Diffuse[4] = { 1.0f, 0.9f, 0.8f, 1.0f };
	GLfloat player_Light_Position[4] = { 0.0f, 1.25f, -3.85f, 1.0f };

	int enemiesLit = 0;
	GLfloat enemy_Light_Position[6][4];
	GLfloat enemy_Light_Diffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

public:
	void updatePlayerLightPosition(float x, float z) {
		player_Light_Position[0] = x;
		player_Light_Position[2] = z;
	}

	void setEnemyLight(float positionX, float positionY, int lightsToInitiate);
	void renderLights();
	void calculate(float dt);
};

