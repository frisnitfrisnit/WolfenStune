//
//  Map.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#ifndef Map_hpp
#define Map_hpp

#include "raylib-cpp.hpp"
#include "LineSegment.hpp"
#include <vector>

class Map
{
public:
	Map();
	virtual ~Map() {}
	
	void CreateMap(int _tileSize);
	void CreateCollisionEdges();

	void DrawMiniMap() const;
	void Draw3DWallProjections();
	
	int IsWallAtPos(const float _xPos, const float _yPos) const { return GetMapAttrib(_xPos, _yPos) != 0; }
	int IsWallAtPosV(const raylib::Vector2& _pos) const { return GetMapAttribV(_pos) != 0; }
	int GetMapAttrib(const float _xPos, const float _yPos) const;
	int GetMapAttribV(const raylib::Vector2& _pos) const;

	int mTileSize;
	int mScreenWidth;
	int mScreenHeight;
	int mWallWidth = 1;

	std::vector<LineSegment> mEdges;
	
private:
	LineSegment CreateLineSegmentFromGrid(const int _startCol, const int _startRow, const int _endCol, const int _endRow);
	raylib::Color GetMapColour(int mapCellType, unsigned char _intensity) const;
};

#endif /* Map_hpp */
