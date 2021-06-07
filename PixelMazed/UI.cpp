#include "UI.h"
#include <string>



UI::UI() {
	for (int i = 0; i < 36; i++) {
		BuildingFunctions::loadTexture(&text_text[i], std::string("gfx/Texts/text_") + std::to_string(i) + (std::string)".png");
	}
	BuildingFunctions::loadTexture(&wall, std::string("gfx/Tiles/BrickWall (0).png"));


}

//WORKS
void UI::drawUiText(float x, float y, float sizeX, float sizeY, Vector3 rgb, std::string text) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glColor3f(rgb.x, rgb.y, rgb.z);
	for (int i = 0; i < text.length(); i++) {

		int textIndex = text[i];
		if (textIndex > 57) {//its a letter, where A is 65(ascii), a is [10]
			textIndex -= 55;
		}
		else {//its a number, where 0 is 48(ascii)
			textIndex -= 48;
		}
		if (text[i] != ' ') {
			BuildingFunctions::makeTextRect(Vector3(x + i * (sizeX), y, 0.0), Vector3(x + i * (sizeX), y - sizeY, 0.0), Vector3(x + sizeX + i * (sizeX), y - sizeY, 0.0), Vector3(x + sizeX + i * (sizeX), y, 0.0), Vector3(0.0, 0.0, 1.0), 1.0, 1.0, &text_text[textIndex]);
		}
	}
	glColor3f(1.f, 1.f, 1.f);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void UI::drawMiniMap() {
	
	
	float mmp_size_x = 0.01f;
	float mmp_size_y = *width / *height * mmp_size_x;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			
			if(explore_progress[y][x]){

				switch (map.getTile(x, y)) {
				case WALL: glColor3f(1, 1, 1); break;
				case LADDER_DOWN: glColor3f(0, 1, 0); break;
				case LADDER_UP: glColor3f(1, 0, 0); break;
				case VENDOR: glColor3f(1, 1, 0); break;
				case DOOR: glColor3f(0.5, 0.5, 0.5); break;
				case UNASSIGNED: break;
				default: glColor3f(0.7, 0.7, 0.7); break;
				}
				glBegin(GL_QUADS);  
				glVertex2f(1 - 50* mmp_size_x + x * mmp_size_x, 1 - y * mmp_size_y);
				glVertex2f(1 - 50* mmp_size_x+ x * mmp_size_x, 1 - y * mmp_size_y + mmp_size_y);
				glVertex2f(1 - 50* mmp_size_x+ x * mmp_size_x + mmp_size_x, 1 - y * mmp_size_y + mmp_size_y);
				glVertex2f(1 - 50* mmp_size_x+ x * mmp_size_x + mmp_size_x, 1 - y * mmp_size_y);
				glEnd();
			}
		}
	}
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS); //player icon
	glVertex2f(1 - 50* mmp_size_x + playerPos[0] * mmp_size_x - mmp_size_x, 1 - playerPos[1] * mmp_size_y + 2*mmp_size_y);
	glVertex2f(1 - 50* mmp_size_x + playerPos[0] * mmp_size_x - mmp_size_x, 1 - playerPos[1] * mmp_size_y);
	glVertex2f(1 - 50* mmp_size_x + playerPos[0] * mmp_size_x + mmp_size_x, 1 - playerPos[1] * mmp_size_y);
	glVertex2f(1 - 50* mmp_size_x + playerPos[0] * mmp_size_x + mmp_size_x, 1 - playerPos[1] * mmp_size_y + 2*mmp_size_y);
	glEnd();
	

	

}

void UI::updateMiniMapProgress(float x_, float y_) {
	//int casts
	int x = x_;
	int y = y_;
	playerPos[0] = x_;
	playerPos[1] = y_;

	//0 unknown
	 //1 seen
	//2 been

	int sightDistance = 5;

	if (explore_progress[y][x] != 2) { //if not already been to this place - saves unnecessary computations
		for (int ydiff = -sightDistance; ydiff <= sightDistance; ydiff++) {
			for (int xdiff = -sightDistance; xdiff <= sightDistance; xdiff++) {
				//failsafe against out of scope access
				if (!(xdiff + x < 0 || xdiff + x > 49 || ydiff + y < 0 || ydiff + y > 49)&& !(xdiff == 0 && ydiff == 0)) {
					if (map.canSee(x_, y_, x_  + xdiff, y_  + ydiff)) {
						explore_progress[y + ydiff][x + xdiff] = 1;
					}
				}
			}
		}	
	}
	explore_progress[y][x] = 2;
}



void UI::setup(float* fov_, float* width_, float* height_, float* nearPlane_, float* farPlane_) {
	fov = fov_;
	width = width_;
	height = height_;
	nearPlane = nearPlane_;
	farPlane = farPlane_;

	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			explore_progress[y][x] = 0;
		}
	}

	
}
void UI::render_Main_Menu() {

	drawUiText(-0.75, 0.95, 0.15, 0.3, Vector3(1.0, 0.0, 0.0), "PIXELMAZED");
	drawUiText(-0.74, 0.94, 0.15, 0.3, Vector3(0.0, 1.0, 0.0), "PIXELMAZED");
	drawUiText(-0.73, 0.93, 0.15, 0.3, Vector3(0.0, 0.0, 1.0), "PIXELMAZED");
	drawUiText(0.5, 0.60, 0.1, 0.2, Vector3(0.0, 0.0, 0.0), "DEMO");

	drawUiText(-0.3, 0.1, 0.15, 0.25, Vector3(0.0, 1.0, 1.0), "PLAY");
	drawUiText(-0.525, -0.2, 0.15, 0.25, Vector3(0.0, 1.0, 0.0), "CREDITS");
	drawUiText(-0.3, -0.5, 0.15, 0.25, Vector3(1.0, 0.0, 0.0), "EXIT");

}
void UI::render_Credits() {
	drawUiText(-0.525, 0.95, 0.15, 0.3, Vector3(1.0, 0.0, 1.0), "CREDITS");
	drawUiText(-0.525, 0.94, 0.15, 0.3, Vector3(1.0, 1.0, 0.0), "CREDITS");
	drawUiText(-0.525, 0.93, 0.15, 0.3, Vector3(0.0, 1.0, 1.0), "CREDITS");

	drawUiText(0.6, 0.90, 0.1, 0.2, Vector3(0.0, 0.0, 0.0), "BACK");

	drawUiText(-1, 0.25, 0.10, 0.15, Vector3(0.0, 0.0, 1.0), "ART N CODE");//10
	drawUiText(-0.55, 0.1, 0.05, 0.10, Vector3(0.0, 0.0, 0.0), "BY");
	drawUiText(-0.65, 0.0, 0.1, 0.2, Vector3(0.0, 0.0, 1.0), "TBP");

	drawUiText(0.25, 0.25, 0.10, 0.15, Vector3(1.0, 0.0, 0.0), "MUSIC");//10
	drawUiText(0.45, 0.1, 0.05, 0.10, Vector3(0.0, 0.0, 0.0), "BY");
	drawUiText(0.1, 0.0, 0.1, 0.2, Vector3(1.0, 0.0, 0.0), "SLEEPY K");

	drawUiText(-0.84, -0.4, 0.12, 0.15, Vector3(0.3, 0.0, 1.0), "LIBRARIES USED");
	drawUiText(-0.2, -0.61, 0.1, 0.1, Vector3(0.0, 0.0, 0.0), "GLUT");
	drawUiText(-0.25, -0.72, 0.1, 0.1, Vector3(0.0, 0.0, 0.0), "BOX2D");
	drawUiText(-0.15, -0.83, 0.1, 0.1, Vector3(0.0, 0.0, 0.0), "SDL");
}

void UI::render_controls() {
	//controls
	drawUiText(-0.95, 0.2, 0.03, 0.06, Vector3(1.0, 1.0, 1.0), std::string("CURRENT CONTROLS"));
	drawUiText(-0.95, 0.14, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("W FORWARD"));
	drawUiText(-0.95, 0.11, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("A LEFT"));
	drawUiText(-0.95, 0.08, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("S BACK"));
	drawUiText(-0.95, 0.05, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("D RIGHT"));
	drawUiText(-0.95, 0.02, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("LMB SHOOT"));
	drawUiText(-0.95, -0.01, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("E GO UP OR DOWN WITH LADDER"));
	drawUiText(-0.95, -0.04, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("M MENU"));
	drawUiText(-0.95, -0.07, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("R RESET"));
	drawUiText(-0.95, -0.1, 0.01, 0.03, Vector3(1.0, 1.0, 1.0), std::string("ESC EXIT"));
}

void UI::render_Game() {

	//healthbar
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS); //player icon
	glVertex2f(-0.5, -0.9);
	glVertex2f(-0.5, -1.0);
	glVertex2f(-0.5 + (float(*playerHP)/200), -1.0);
	glVertex2f(-0.5 + (float(*playerHP)/200), -0.9);
	glEnd();


	drawMiniMap();

	drawUiText(-0.15, 0.95, 0.05, 0.1, Vector3(1.0, 1.0, 1.0), "SCORE");
	drawUiText(0.15, 0.95, 0.05, 0.1, Vector3(1.0, 1.0, 1.0), std::to_string(*score_));

	drawUiText(-1, -0.9, 0.05, 0.1, Vector3(1.0, 1.0, 0.7), std::string("FLOOR"));
	drawUiText(-0.7, -0.9, 0.05, 0.1, Vector3(1.0, 1.0, 0.7), std::to_string(map.getLevel()));

	render_controls();
}

void UI::render_Game_Over() {

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS); //RED BG
	glVertex2f(-1, 1);
	glVertex2f(-1, -1.0);
	glVertex2f(1, -1.0);
	glVertex2f(1,2);
	glEnd();

	render_controls();

	drawUiText(-0.45, 0.3, 0.1, 0.2, Vector3(1.0, 1.0, 0.7), std::string("GAME OVER"));
	drawUiText(-0.4, 0.0, 0.1, 0.2, Vector3(1.0, 1.0, 0.7), std::string("YOU DIED"));

}
void UI::render_UI(gameState GameState) {
	// Swap to 2D rendering
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(1.f, 1.f, 1.f);

	if (GameState == CREDITS || GameState == MAIN_MENU) {
		BuildingFunctions::makeTextRect(Vector3(-1, 1 + bgIt, 0), Vector3(-1, -3 + bgIt, 0), Vector3(1, -3 + bgIt, 0), Vector3(1, 1 + bgIt, 0), Vector3(0, 0, 1), 6, 2, &wall);
	}
	switch (GameState) {
	case MAIN_MENU:render_Main_Menu(); break;
	case GAME:render_Game(); break;
	case CREDITS:render_Credits(); break;
	case GAME_OVER:render_Game_Over();
	}


	glColor3f(1.f, 1.f, 1.f);
	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(*fov, (*width / *height), *nearPlane, *farPlane);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}
