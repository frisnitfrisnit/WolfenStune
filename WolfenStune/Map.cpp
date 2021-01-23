//
//  Map.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Map.hpp"
#include "Game.hpp"
#include "raylib-cpp.hpp"

const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;
#define CAST_METHOD_WOLFENSTEIN 0
#define CAST_METHOD_GENERATE_LINE_SEGMENTS 1
#define CAST_METHOD CAST_METHOD_WOLFENSTEIN // 0 = Wolfenstein, 1 = Generate Line Segments

raylib::Color DARK_GREY(32,32,32,255);

//const int WINDOW_WIDTH = MAP_NUM_COLS * mTileSize;
//const int WINDOW_HEIGHT = MAP_NUM_ROWS * mTileSize;

int grid[MAP_NUM_ROWS][MAP_NUM_COLS] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
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

void Map::CreateMap(int _tileSize)
{
	mTileSize = _tileSize;
#if CAST_METHOD == CAST_METHOD_GENERATE_LINE_SEGMENTS
	CreateCollisionEdges();
#endif
}

void Map::CreateCollisionEdges()
{
#if CAST_METHOD == CAST_METHOD_GENERATE_LINE_SEGMENTS
	mEdges.clear();
	//int startRow = -1;
	for(int r = 0; r<MAP_NUM_ROWS; r++)
	{
		int startCol = -1;
		for(int c = 0; c<MAP_NUM_COLS; c++)
		{
			if(grid[r][c] != 0) // is wall
			{
				printf("Checking R%d,C%d (%d): ", r, c, grid[c][r]);
				// start/continue a wall LineSegment
				if(r + 1 < MAP_NUM_ROWS && grid[r + 1][c] == 0)
				{
					if(startCol == -1)
					{
						startCol = c;
						printf("< NewSegment\n");
					}
					else
					{
						if(c + 1 < MAP_NUM_COLS)
						{
							if(grid[r + 1][c] != 0 && startCol != -1)
							{
								printf("> Ending Segment (mid)\n");
								mEdges.push_back(CreateLineSegmentFromGrid(r, startCol, r, c));
								startCol = -1;
							}
							else
								printf("- Continuing Segment\n");
						}
						else
						{
							// Row ended, check if we need to finish a segment
							if(startCol != -1)
							{
								printf("> Ending Segment (end)\n");
								mEdges.push_back(CreateLineSegmentFromGrid(r, startCol, r, c));
								startCol = -1;
							}
							else
								printf("No action\n");
						}
					}
				}
				else
				{
					if(startCol != -1)
					{
						printf("> Ending Segment (mid)\n");
						mEdges.push_back(CreateLineSegmentFromGrid(r, startCol, r, c));
						startCol = -1;
					}
					else
						printf("Blocked Below\n");
				}
			}
			else
			{
				if(startCol != -1)
				{
					printf("> Ending Segment (mid)\n");
					mEdges.push_back(CreateLineSegmentFromGrid(r, startCol, r, c));
					startCol = -1;
				}
				else
					printf("Floor\n");
			}
		}
	}
#endif
}

LineSegment Map::CreateLineSegmentFromGrid(const int _startCol, const int _startRow, const int _endCol, const int _endRow)
{
	//if(bottom)
	LineSegment newSegment(_startRow * mTileSize, _startCol * mTileSize + (mTileSize - 1), _endRow * mTileSize, _endCol * mTileSize + (mTileSize - 1));
	return newSegment;
}

void Map::DrawMap() const
{
	const float scale = Game::mMiniMapScaleFactor;
	for(int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for(int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * mTileSize;
			int tileY = i * mTileSize;
			const raylib::Color tileColor = grid[i][j] == 1 ? DARK_GREY : WHITE;
			DrawRectangle(tileX * scale, tileY * scale, mTileSize * scale, mTileSize * scale, tileColor);
			if(grid[i][j] == 0)
				DrawRectangleLines(tileX * scale, tileY * scale, mTileSize * scale, mTileSize * scale, DARK_GREY);
		}
	}
	
#if CAST_METHOD == CAST_METHOD_GENERATE_LINE_SEGMENTS
	for(auto& e:mEdges)
	{
		DrawLineV(e.mStartPos, e.mEndPos, YELLOW);
	}
#endif
}

int Map::GetMapAttrib(const float _xPos, const float _yPos) const
{
	int x = _xPos / mTileSize;
	int y = _yPos / mTileSize;
	if(x >= 0 && x < MAP_NUM_COLS && y >= 0 && y < MAP_NUM_ROWS)
		return grid[y][x];
	
	return -1;
}

int Map::GetMapAttribV(const raylib::Vector2& _pos) const
{
	return(GetMapAttrib(_pos.x, _pos.y));
}
