#pragma once

#include "Level.h"
#include "Camera.h"
#include "AudioManager.h"
//GameManager

class GameManager
{ 
private:
	gameState state_ = MAIN_MENU;

	AudioManager audio_manager;

	std::vector<Level> levels;
	int score = 0;
	int currentLevel =0;

	float spawnClock = 0;

	//config Glut variables for rendering UI
	float config_width;
	float config_height;
	float config_fov_;
	float config_nearPlane_;
	float config_farPlane_;

	Camera camera_;

	//textures
	GLuint cobble_textures[3];
	GLuint brickWall_textures[7];
	GLuint woodTexture;
	GLuint trapdoortxt;
	GLuint skeleton_txt;
	GLuint chests_txt[9];//textures in ordr: front(i),side(i), topbot(i) where i is tier (1-3)

	BodiedEntity Player;

	bool keyDown = false;
public:
	GameManager();
	void bindPlayerBody() { Player.setBody(levels.at(currentLevel - 1).get_player_body_LEVELLOCAL()); }
	void goUpLevel() { if (currentLevel > 1) { currentLevel--; bindPlayerBody(); } }
	void goDownLevel();
	void renderLevel();
	void updateLevel(float dt);
	void handle_input(Input& input, float dt);

	void getConfigurationVariables(int width, int height, float fov_, float nearPlane_, float farPlane_) {
		config_width = width;
		config_height = height;
		config_fov_ = fov_;
		config_nearPlane_ = nearPlane_;
		config_farPlane_ = farPlane_;


	}

	void setCam();
};