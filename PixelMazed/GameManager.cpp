#include "GameManager.h"
#include <string>
#include <freeglut.h>

GameManager::GameManager() {
	goDownLevel();
	BuildingFunctions::loadTexture(&woodTexture, "gfx/Tiles/wood.png");

	for (int i = 0; i < 10; i++) {
		if (i < 3) {
			BuildingFunctions::loadTexture(&cobble_textures[i], std::string("gfx/Tiles/CobbleStone (") + std::to_string(i) + (std::string)").png");
			BuildingFunctions::loadTexture(&chests_txt[i*3], std::string("gfx/Chests/chest_tier_") + std::to_string(i+1) + (std::string)"_front.png");
			BuildingFunctions::loadTexture(&chests_txt[i*3+1], std::string("gfx/Chests/chest_tier_") + std::to_string(i+1) + (std::string)"_side.png");
			BuildingFunctions::loadTexture(&chests_txt[i*3+2], std::string("gfx/Chests/chest_tier_") + std::to_string(i+1) + (std::string)"_topbot.png");
		}
		if (i < 7) {
			BuildingFunctions::loadTexture(&brickWall_textures[i], std::string("gfx/Tiles/BrickWall (") + std::to_string(i) + (std::string)").png");
		}
	}

	BuildingFunctions::loadTexture(&skeleton_txt, "gfx/Enemies/SkeleMage.png");
	Player.setHealth(200);
	
}


void GameManager::goDownLevel() {
	currentLevel++;
	if (levels.size() < currentLevel) { //if the player hasnt been so deep yet, create a new level
		Level tempLevel(currentLevel);
		levels.push_back(tempLevel);
		levels.back().getUI()->setup(&config_fov_, &config_width, &config_height, &config_nearPlane_, &config_farPlane_);
		levels.back().setupLevel(brickWall_textures, cobble_textures,chests_txt);
		levels.back().bindScoreToCol(&score);
		levels.back().spawnSkeletons();
		levels.back().BindPlayerHP(Player.getHealth());
	}
	bindPlayerBody();
}

void GameManager::setCam() {
	gluLookAt(camera_.position.x, camera_.position.y, camera_.position.z, camera_.lookat.x, camera_.lookat.y, camera_.lookat.z, camera_.up.x, camera_.up.y, camera_.up.z);
}

void GameManager::renderLevel() {

	if (state_ == GAME) {
		levels.at(currentLevel - 1).render_level(&woodTexture, &skeleton_txt, &woodTexture);
	}

	levels.at(currentLevel - 1).getUI()->render_UI(state_);
}


void GameManager::updateLevel(float dt) {
	if (state_ == GAME) {
		levels.at(currentLevel - 1).update_level(dt);
		Player.incrementCoolDown(dt);
		spawnClock += dt;
		if (spawnClock > 20) {
			spawnClock = 0;
			levels.at(currentLevel - 1).spawnSkeletons();
		}
		if (*Player.getHealth() <= 0) {
			state_ = GAME_OVER;
		}
	}
	else{
		levels.at(currentLevel - 1).getUI()->incBgDt(dt);
	}
	audio_manager.updateSound();

}

void GameManager::handle_input(Input& input,float dt) {

	if (input.isKeyDown('m') || input.isKeyDown('M')) {//QUICK MENU
		state_ = MAIN_MENU;
		audio_manager.endMusic();
		audio_manager.play_Title_Song();
		glutSetCursor(GLUT_CURSOR_BOTTOM_SIDE);
	}

	if (state_ == GAME) {
		

		b2Vec2 linVec_(0.0f, 0.0f);//TEMP INPUT CLASS!

		if (input.isKeyDown('w') || input.isKeyDown('W')) {
			linVec_ += b2Vec2(camera_.forward.x, camera_.forward.z);
		}
		else if (input.isKeyDown('s') || input.isKeyDown('S')) {
			linVec_ -= b2Vec2(camera_.forward.x, camera_.forward.z);
		}

		if (input.isKeyDown('d') || input.isKeyDown('D')) {
			linVec_ += b2Vec2(camera_.right.x, camera_.right.z);
		}
		else if (input.isKeyDown('a') || input.isKeyDown('A')) {
			linVec_ -= b2Vec2(camera_.right.x, camera_.right.z);

		}

		if (input.isKeyDown('e') || input.isKeyDown('E')) {//USE
			if (!keyDown) {
				keyDown = true;
				if (std::abs(camera_.position.x - levels.at(currentLevel - 1).ladder_down_Getpos().x) < 1 && std::abs(camera_.position.z - levels.at(currentLevel - 1).ladder_down_Getpos().y) < 1) {
					goDownLevel();
				}
				else if (std::abs(camera_.position.x - levels.at(currentLevel - 1).ladder_up_Getpos().x) < 1 && std::abs(camera_.position.z - levels.at(currentLevel - 1).ladder_up_Getpos().y) < 1) {
					goUpLevel();
				}
			}
		}

		

		if (input.isKeyDown('r') || input.isKeyDown('R')) {//QUICK RESTET
			if (!keyDown) {
				keyDown = true;
				levels.clear();
				currentLevel = 0;
				goDownLevel();
				Player.setHealth(200);
			}
		}

		//fix against lots of executes on hold
		if (!input.isKeyDown('r') && !input.isKeyDown('R') && !input.isKeyDown('e') && !input.isKeyDown('E')) {
			keyDown = false;
		}

		camera_.position.x = levels.at(currentLevel - 1).get_player_body_LEVELLOCAL()->GetPosition().x;
		camera_.position.z = levels.at(currentLevel - 1).get_player_body_LEVELLOCAL()->GetPosition().y;
		camera_.updateLookAt();
		camera_.InputMovement(input, dt, config_width, config_height);
		linVec_.Normalize();
		linVec_.x *= 3;
		linVec_.y *= 3;
		levels.at(currentLevel - 1).get_player_body_LEVELLOCAL()->SetLinearVelocity(linVec_);

		b2Vec2 playerForward = b2Vec2(camera_.forward.x, camera_.forward.z);

		playerForward.Normalize();

		if (input.isMouseLDown() && Player.canShoot()) {
			Player.resetCD();
			levels.at(currentLevel - 1).shootBullett(Player.getPosition(), playerForward, true);
		}


		glutWarpPointer(config_width / 2, config_height / 2);
	}

	else if (state_ == MAIN_MENU) {
		
		
		if (input.isMouseLDown()) {

			float xpos = float(input.getMouseX()) / config_width * 2 - 1; //pos cursor -1 to 1
			float ypos = float(input.getMouseY()) / config_height * -2 + 1; //pos cursor -1 to 1

			//temp hardcoded ui button pos
			if (xpos > -0.525 && xpos < 0.525) {
				if (ypos < -0.2 && ypos > -0.45) {//credits
					state_ = CREDITS;
					
				}
				else if (xpos > -0.3 && xpos < 0.3) {//since they are the same size
					if (ypos > -0.15 && ypos < 0.1) {//play
						state_ = GAME;
						audio_manager.endMusic();
						audio_manager.play_Game_Song();
						glutSetCursor(GLUT_CURSOR_NONE);
					}
					else if (ypos > -0.75 && ypos < -0.5) {//exit
						glutLeaveMainLoop();
					}
				}
			}
		}

	}

	else if (state_ == CREDITS) {
		if (input.isMouseLDown()) {

			float xpos = float(input.getMouseX()) / config_width * 2 - 1; //pos cursor -1 - 1
			float ypos = float(input.getMouseY()) / config_height * -2 + 1; //pos cursor -1 - 1

			//temp hardcoded ui button pos
			if (xpos > 0.6 && xpos <1.0) {
				if (ypos < 0.9 && ypos > 0.7) {//credits
					state_ = MAIN_MENU;
				}
			}
		}
	}
	else if (state_ == GAME_OVER) {
		if (input.isKeyDown('r') || input.isKeyDown('R')) {//QUICK RESTET
			if (!keyDown) {
				keyDown = true;
				levels.clear();
				currentLevel = 0;
				goDownLevel();
				Player.setHealth(200);
				state_ = GAME;
			}
		}
	}
}