//
//  Ray2d.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 14/01/2021.
//

#include "Ray2d.hpp"

Ray2d::Ray2d(const raylib::Vector2& _pos, const float _angle)
{
	mPos = _pos;
	mAngle = _angle;
}
