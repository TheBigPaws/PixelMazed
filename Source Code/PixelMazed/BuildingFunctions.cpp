#include "BuildingFunctions.h"
#include <iostream>

void BuildingFunctions::loadTexture(GLuint* loadTo, std::string name) {

	const char* charredName = name.c_str();
	*loadTo = SOIL_load_OGL_texture(
		charredName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void BuildingFunctions::makeBlock(GLfloat MidPozX, GLfloat MidPozY, GLfloat MidPozZ, GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ, GLfloat scaleTXTvSIZE, GLuint * texture) {
	
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glBegin(GL_QUADS);
	//FRONT
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	//RIGHT
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(sizeZ / scaleTXTvSIZE, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(sizeZ / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	//back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(sizeZ / scaleTXTvSIZE, sizeY / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(sizeZ / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, sizeZ / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, sizeZ / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY + sizeY / 2, MidPozZ - sizeZ / 2);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, sizeZ / scaleTXTvSIZE);
	glVertex3f(MidPozX - sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, sizeZ / scaleTXTvSIZE);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ + sizeZ / 2);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(sizeX / scaleTXTvSIZE, 0.0f);
	glVertex3f(MidPozX + sizeX / 2, MidPozY - sizeY / 2, MidPozZ - sizeZ / 2);

	glEnd();

}

void BuildingFunctions::makeTextRect(Vector3 leftup, Vector3 leftdown, Vector3 rightdown, Vector3 rightup, Vector3 normal, GLfloat textreachX_, GLfloat textreachY_, GLuint * texture) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(leftup.x, leftup.y, leftup.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(0.0f, textreachY_);
	glVertex3f(leftdown.x, leftdown.y, leftdown.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(textreachX_, textreachY_);
	glVertex3f(rightdown.x, rightdown.y, rightdown.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(textreachX_, 0.0f);
	glVertex3f(rightup.x, rightup.y, rightup.z);

	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void BuildingFunctions::makeTextRectXY(Vector3 positionLeftUp, Vector3 Size, GLfloat textreachX_, GLfloat textreachY_, GLuint* texture){

	//enables

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glNormal3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(positionLeftUp.x, positionLeftUp.y, 0.0);

	//glNormal3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, textreachY_);
	glVertex3f(positionLeftUp.x, positionLeftUp.y - Size.y, 0.0);

	//glNormal3f(0.0, 0.0, 0.1);
	glTexCoord2f(textreachX_, textreachY_);
	glVertex3f(positionLeftUp.x + Size.x, positionLeftUp.y - Size.y, 0.0);

	//glNormal3f(0.0, 0.0, 0.1);
	glTexCoord2f(textreachX_, 0.0f);
	glVertex3f(positionLeftUp.x + Size.x, positionLeftUp.y, 0.0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glBegin(GL_QUADS);
	
	glEnd();

	//set back

	glDisable(GL_TEXTURE_2D);
}


void BuildingFunctions::makeTextTria(Vector3 vert1, Vector3 vert2, Vector3 vert3, Vector3 normal, Vector3 textv1, Vector3 textv2, Vector3 textv3, GLuint * texture) {
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glBegin(GL_TRIANGLES);
	//FRONT
	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(textv1.x, textv1.y);
	glVertex3f(vert1.x, vert1.y, vert1.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(textv2.x, textv2.y);
	glVertex3f(vert2.x, vert2.y, vert2.z);

	glNormal3f(normal.x, normal.y, normal.z);
	glTexCoord2f(textv3.x, textv3.y);
	glVertex3f(vert3.x, vert3.y, vert3.z);

	glEnd();

}


textRect::textRect(Vector3 leftup_, Vector3 leftdown_, Vector3 rightdown_, Vector3 rightup_, Vector3 normal_, GLfloat textreachX_, GLfloat textreachY_, GLuint * texture_) {
	leftup = leftup_;
	leftdown = leftdown_;
	rightdown = rightdown_;
	rightup = rightup_;
	normal = normal_;
	texture = texture_;
	textreachX = textreachX_;
	textreachY = textreachY_;

}

void textRect::render_rect() {
	BuildingFunctions::makeTextRect(leftup, leftdown, rightdown, rightup, normal, textreachX, textreachY, texture);
}