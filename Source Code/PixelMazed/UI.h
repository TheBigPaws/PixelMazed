#pragma once
#include "Map.h"
#include "BuildingFunctions.h"
enum gameState{MAIN_MENU,GAME_OVER,GAME,CREDITS};

class UI
{
private:
	int explore_progress[50][50]; //0 for unexplored, 1 for seen, 2 for been_to. 2 for performance boost
	float * fov, * width, * height, * nearPlane, * farPlane;
	float bgIt = 0;
	//float colourMove = 0;
	Map map;
	float playerPos[2];
	GLuint text_text[36];//48-57 = 0-9 | 97 - 122 a-z
	GLuint wall;
	int* playerHP;
protected:
	//starts drawing the text, origin is up left
	void drawUiText(float x, float y, float sizeX, float sizeY, Vector3 rgb, std::string text);

	void render_Game_Over();
	void render_Main_Menu();
	void render_Credits();
	void render_controls();
	void render_Game();
	void drawMiniMap();

	

public:
	int* score_;
	UI();
	void get_map(Map map_) {
		map = map_;
	}
	void setup(float* fov_, float* width_, float* height_, float* nearPlane_, float* farPlane_);
	void updateMiniMapProgress(float x_, float y_); //utilize
	void incBgDt(float dt) {
		bgIt += dt * 0.2;
		if (bgIt > 2) { bgIt = 0.0; }
	}
	void bindHP(int* player_hp) { playerHP = player_hp; }
	void render_UI(gameState GameState);
};

