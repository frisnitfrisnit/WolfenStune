//
//  Map.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Map.hpp"
#include "raylib-cpp.hpp"
const int TILE_SIZE = 32;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;

raylib::Color DARK_GREY(32,32,32,255);

//const int WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
//const int WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

int grid[MAP_NUM_ROWS][MAP_NUM_COLS] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Map::Map()
{
}

void Map::CreateMap()
{
}

void Map::DrawMap() const
{
	for(int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for(int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE;
			int tileY = i * TILE_SIZE;
			const raylib::Color tileColor = grid[i][j] == 1 ? DARK_GREY : WHITE;
			DrawRectangle(tileX, tileY, TILE_SIZE, TILE_SIZE, tileColor);
			if(grid[i][j] == 0)
				DrawRectangleLines(tileX, tileY, TILE_SIZE, TILE_SIZE, DARK_GREY);
		}
	}
}

int Map::GetMapAttrib(const raylib::Vector2& _pos) const
{
	int x = _pos.x / TILE_SIZE;
	int y = _pos.y / TILE_SIZE;
	if(x >= 0 && x < MAP_NUM_COLS && y >= 0 && y < MAP_NUM_ROWS)
		return grid[y][x];
	
	return -1;
}
