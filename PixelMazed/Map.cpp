#include "Map.h"

Map::Map() {
	srand(time(NULL));
}

//pos is the most leftup EMPTY square of the room so.
void Map::createRoom(int pos_x, int pos_y, int sizeX, int sizeY, RoomType roomType) {
	
	for (int y = pos_y-1; y <= pos_y +sizeY; y++) { //create walls and room tiles
		for (int x = pos_x-1; x <= pos_x + sizeX ; x++) {
			if (x == pos_x - 1 || y == pos_y - 1 || x == pos_x + sizeX || y == pos_y + sizeY) {
				if (layout[y][x] == UNASSIGNED) {
					layout[y][x] = WALL;
				}
			}
			else {
				layout[y][x] = FLOOR;
			}
			
		}
	}
	
	
	//now roll for good and bad features, increasing with level

	//ANY room
	if (rand() % (6 - level) == 0) { //treasure. chance: 1 in (6-level). caps at 5, where every room will have a treasure chest
		layout[pos_y + rand() % sizeY][pos_x + rand() % sizeX] = CHEST;
	}

	//additional room feature
	switch (roomType) {
		case NORMAL: 
			for (int i = 0; i < 1 + rand() % (1 + level); i++) { //iterations to place traps. number: 1 to 2+level
				if (rand() % 4 == 0) {
					layout[pos_y + rand() % sizeY][pos_x + rand() % sizeX] = TRAP_PORT;
				}
				else { layout[pos_y + rand() % sizeY][pos_x + rand() % sizeX] = TRAP_SPIKE; }
			}
		break;
		case SHOP:
			layout[pos_y + rand() % sizeY][pos_x + rand() % sizeX] = VENDOR;
		break;
		case TREASURE:
			for (int i = 0; i < 1 + rand() % (4 + level * 2); i++) {
				layout[pos_y + rand() % sizeY][pos_x + rand() % sizeX] = CHEST;
			}
		break;
	}

	rooms.push_back(Room(sizeX, sizeY, pos_x, pos_y, roomType));
}


//creates an empty walled corridor //IMPORTANT! first position is the one that will go on X
void Map::createHallway(int from_x, int from_y, int to_x, int to_y) {

	int difference[2] = { to_y - from_y, to_x - from_x }; // Y , X !!
	int ops[2]; // Y, X!

	if (difference[0] != 0) { //dont devide by 0
		ops[0] = difference[0] / abs(difference[0]);
	}
	else { ops[0] = 0; }
	if (difference[1] != 0) {
		ops[1] = difference[1] / abs(difference[1]);
	} 
	else{ ops[1] = 0; }

	for (int i = 0; i < abs(difference[1] + ops[1]*2); i++) { // go horizontal first
		if (layout[from_y][from_x + ops[1] * i] == UNASSIGNED || layout[from_y][from_x + ops[1] * i] == WALL) {

			if (layout[from_y + 1][from_x + ops[1] * i] != HALLWAY) {//fix against overlapping and blocking other corridors
				layout[from_y + 1][from_x + ops[1] * i] = WALL;
			}
			layout[from_y][from_x + ops[1] * i] = HALLWAY;
			if (layout[from_y - 1][from_x + ops[1] * i] != HALLWAY) { 
				layout[from_y - 1][from_x + ops[1] * i] = WALL; 
			}
			if (layout[from_y][from_x + ops[1] * i + 1] == FLOOR || layout[from_y][from_x + ops[1] * i - 1] == FLOOR) { //door condition
				layout[from_y][from_x + ops[1] * i] = DOOR;
			}
		}
	}


	for (int i = 0; i < abs(difference[0] + ops[0]*2); i++) { // then vertical
		if (layout[to_y - ops[0] * i][to_x] == UNASSIGNED || layout[to_y - ops[0] * i][to_x] == WALL) {

			if (layout[to_y - ops[0] * i][to_x + 1] != HALLWAY) { //fix against overlapping and blocking other corridors
				layout[to_y - ops[0] * i][to_x + 1] = WALL;
			}
			layout[to_y - ops[0] * i][to_x] = HALLWAY;       //-ops because ops is an opposite vector
			if (layout[to_y - ops[0] * i][to_x - 1] != HALLWAY){
				layout[to_y - ops[0] * i][to_x - 1] = WALL;
			}
			if (layout[to_y - ops[0] * i - 1][to_x] == FLOOR || layout[to_y - ops[0] * i + 1][to_x] == FLOOR) { //door condition
				layout[to_y - ops[0] * i][to_x] = DOOR;
			}
		}
	}

	//buildFixes : empty corner and fill wall
	layout[from_y + ops[0]][to_x] = HALLWAY;
	layout[from_y][to_x - ops[1]] = HALLWAY;
	if (layout[from_y][to_x + ops[1] * 2] == WALL || layout[from_y][to_x + ops[1] * 2] == UNASSIGNED) { //error check for forking hallways
		layout[from_y][to_x + ops[1]] = WALL;
	}
	if (layout[from_y - ops[0]*2][to_x] == WALL || layout[from_y - ops[0]*2][to_x] == UNASSIGNED) {
		layout[from_y - ops[0]] [to_x] = WALL;
	}
}

void Map::createWall(int pos_x, int pos_y, Direction direction) {

	int dirX = 0;
	int dirY = 0;

	switch (direction)
	{
	case UP : dirY--; break;
	case DOWN : dirY++; break;
	case LEFT : dirX--; break;
	case RIGHT : dirX++; break;
	}

	while (layout[pos_y][pos_x] != WALL) {

		if (layout[pos_y][pos_x] == UNASSIGNED) {
			layout[pos_y][pos_x] = WALL;
			pos_x += dirX;
			pos_y += dirY;
		}
	}
}

//overload for a specific lentgh
void Map::createWall(int pos_x, int pos_y, Direction direction, int length) {

	int dirX = 0;
	int dirY = 0;
	switch (direction)
	{
	case UP: dirY--; break;
	case DOWN: dirY++; break;
	case LEFT: dirX--; break;
	case RIGHT: dirX++; break;
	}

	for (int i = 0; i < length; i++)
	{
		if (layout[pos_y][pos_x] != FLOOR && layout[pos_y][pos_x] != HALLWAY) {
			layout[pos_y][pos_x] = WALL;
			pos_x += dirX;
			pos_y += dirY;
		}
		else { std::cout << "failed to write a wall on " << pos_x - dirX << " " << pos_y - dirY << std::endl; }
	}
}

void Map::placeEntAndExit() {

	//int entX, entY, exitX, exitY; //exit and entrance room vars;

	entX = 5 + (rand() % (lvlSizeX - 10)); // random entrance
	entY = 5 + (rand() % (lvlSizeY - 10));
	createRoom(entX - 1, entY - 1, 3, 3, NORMAL);
	layout[entY][entX] = LADDER_UP;
	connectRooms(rooms.back(), rooms.at(rand() % (rooms.size() - 1))); //create exit

	exitX = 5 + (rand() % (lvlSizeX - 10));
	exitY = 5 + (rand() % (lvlSizeY - 10));

	while (exitY == entY && exitX == entX) { //error handle, stops from rewriting the entry
		exitX = 2 + (rand() % lvlSizeX - 10);
		exitY = 2 + (rand() % lvlSizeY - 10);
	}
	createRoom(exitX - 1, exitY - 1, 3, 3, NORMAL);
	connectRooms(rooms.back(), rooms.at(rand() % (rooms.size() - 1))); //create exit
	layout[exitY][exitX] = LADDER_DOWN;
}

//randomly connects 2 rooms
void Map::connectRooms(Room room1, Room room2) {
	//logic of connecting rooms 
	createHallway(room1.x + (rand() % room1.sizeX), room1.y + (rand() % room1.sizeY), room2.x + (rand() % room2.sizeX), room2.y + (rand() % room2.sizeY));
}

void Map::printMap() {
	//print
	for (int y = 0; y < lvlSizeY; y++) {
		for (int x = 0; x < lvlSizeX; x++) {
			std::cout << layout[y][x] << " ";
		}
		std::cout << std::endl;
	}
}
void Map::generateMap() {


	for (int y = 0; y < lvlSizeY; y++) { //assigns empty spaces
		for (int x = 0; x < lvlSizeX; x++) {
			layout[y][x] = UNASSIGNED;
		}
	}


	
	createRoom(2 + rand() % (lvlSizeX - 10), 2 + rand() % (lvlSizeX - 10), 3 + rand()%5, 3 + rand() % 5,  NORMAL);

	int nrRooms = 5 + rand() % (level*2); //how many rooms to make. bigger levels make bigger
	int randRoomX,randRoomY; //room creating loop
	for (int i = 0; i < nrRooms; i++) {
		randRoomX = 2 + rand() % (lvlSizeX - 6); //2- 45
		randRoomY = 2 + rand() % (lvlSizeY - 6);

		createRoom(randRoomX, randRoomY, 3 + ((lvlSizeX - randRoomX - 5) % (1+rand()%10)), 3+((lvlSizeY - 5 - randRoomY) % (1 + rand() % 10)), NORMAL); //room on random location and size (but capped at 10);
		connectRooms(rooms.back(), rooms.at(rand()%(rooms.size()-1)));
	}

	placeEntAndExit();

	
}

bool Map::canSee(float fromX, float fromY, float toX, float toY) {
	float checkits = abs(fromX - toX) + abs(fromY - toY); //check more times for longer distances
	for (int rayCheck = 1; rayCheck <= checkits; rayCheck++) {
		float offset[2]{ (toX - fromX) / checkits * float(rayCheck),
						 (toY - fromY) / checkits * float(rayCheck) };
		if (int(fromX + offset[0]) == int(toX) && int(fromY + offset[1]) == int(toY)) {//if the ray has reached the end position
			return true;
		}
		if (layout[int(fromY + offset[1])][int(fromX + offset[0])] == WALL) { //if the point on the ray is on a wall
			return false;
		}
	}
	return true;
}