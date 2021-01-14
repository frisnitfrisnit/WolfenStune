//
//  Map.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#ifndef Map_hpp
#define Map_hpp

#include "raylib-cpp.hpp"

class Map
{
public:
	Map();
	virtual ~Map() {}
	
	void CreateMap();
	void DrawMap() const;
	
	int IsWallAtPos(const raylib::Vector2& _pos) const { return GetMapAttrib(_pos) != 0; }
	int GetMapAttrib(const raylib::Vector2& _pos) const;

};

#endif /* Map_hpp */
