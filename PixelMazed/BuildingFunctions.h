#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <string>
#include "Vector3.h"

class BuildingFunctions
{
public:
	static void makeBlock(GLfloat MidPozX, GLfloat MidPozY, GLfloat MidPozZ, GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ,GLfloat scaleTXTvSIZE, GLuint * texture);
	static void makeTextRect(Vector3 leftup, Vector3 leftdown, Vector3 rightdown, Vector3 rightup, Vector3 normal, GLfloat textreachX_, GLfloat textreachY_, GLuint * texture);
	static void makeTextRectXY(Vector3 positionLeftUp, Vector3 Size, GLfloat textreachX_, GLfloat textreachY_, GLuint* texture);
	static void makeTextTria(Vector3 vert1, Vector3 vert2, Vector3 vert3, Vector3 normal, Vector3 textv1, Vector3 textv2, Vector3 textv3, GLuint * texture);
	static void loadTexture(GLuint* loadTo, std::string name);
};

struct textRect {
	Vector3 leftup;
	Vector3 leftdown;
	Vector3 rightdown;
	Vector3 rightup;
	Vector3 normal;
	GLuint * texture;

	GLfloat textreachX;
	GLfloat textreachY;

	textRect();
	textRect(Vector3 leftup_, Vector3 leftdown_, Vector3 rightdown_, Vector3 rightup_, Vector3 normal_, GLfloat textreachX_, GLfloat textreachY_,  GLuint * texture_);
	void render_rect();
};