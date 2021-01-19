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
	
	float NormalizeAngle(const float _angle) const;
	bool Cast(int _columnID);
	
	raylib::Vector2 mPos;
	float mAngle;

	raylib::Vector2 mIntersection;
	float mLength;
	bool mWasHitVertical;
	
	bool isRayFacingUp;
	bool isRayFacingDown;
	bool isRayFacingLeft;
	bool isRayFacingRight;

};

#endif /* Ray2d_hpp */
