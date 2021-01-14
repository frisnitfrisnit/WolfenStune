//
//  Ray2d.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 14/01/2021.
//

#ifndef Ray2d_hpp
#define Ray2d_hpp

#include "raylib-cpp.hpp"

struct Ray2d
{
	Ray2d(const raylib::Vector2& _pos, const float _angle);
	
	raylib::Vector2 mPos;
	float mAngle;
};

#endif /* Ray2d_hpp */
