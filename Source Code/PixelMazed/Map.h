#pragma once
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <queue>

//enums for code readability
enum Tile { UNASSIGNED, WALL, CHEST, LADDER_UP, LADDER_DOWN, DOOR, FLOOR, HALLWAY, TRAP_SPIKE, TRAP_PORT, VENDOR };
enum Direction {UP, DOWN, LEFT, RIGHT, RANDOM};
enum RoomType {BOSS, SHOP, TREASURE, NORMAL};
enum State {OPEN, CLOSED, OPENING, CLOSING};



struct Room
{
	
	int sizeX, sizeY;
	int x,y;
	RoomType type;
	//great band, come on baby light my fire \m/

	Room();
	Room(int sizeX_, int sizeY_, int pos_x, int pos_y, RoomType tp) { sizeX = sizeX_; sizeY = sizeY_; x = pos_x; y  = pos_y; type = tp; };
};

class Map
{
private:
	Tile layout[50][50];
	int floodPathArr[50][50];
	int level;
	int lvlSizeX = 50;
	int lvlSizeY = 50;
	std::vector<Room> rooms;
	int entX, entY, exitX, exitY; //exit and entrance room vars;
protected:
	//map generation functions
	void createWall(int pos_x, int pos_y, Direction direction);
	void createWall(int pos_x, int pos_y, Direction direction, int length);
	void createRoom(int pos_x, int pos_y, int sizeX, int sizeY, RoomType roomType); //creates a room and returns it
	void placeEntAndExit();
	void connectRooms(Room room1, Room room2);
	void createHallway(int from_x, int from_y, int to_x, int to_y);
	void generateMap();

public:
	Map();
	Map(int lvl) {
		level = lvl;
		generateMap();
	};
	
	//getters
	std::vector<int> getEntPos() { return std::vector<int>{ entX, entY }; };
	std::vector<int> getExitPos() { return std::vector<int>{ exitX, exitY }; };
	Room getRandomRoom() { return rooms.at(rand()%rooms.size()); }

	void printMap();
	Tile getTile(int x, int y) { return layout[y][x]; }
	
	int getLevel() { return level; }

	//simple raycast func
	bool canSee(float fromX, float fromY, float toX, float toY);

};
