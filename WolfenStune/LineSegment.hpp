//
//  LineSegment.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 14/01/2021.
//

#ifndef LineSegment_hpp
#define LineSegment_hpp

#include "raylib-cpp.hpp"

class LineSegment
{
public:
	LineSegment() {}
	
	LineSegment(float x1, float y1, float x2, float y2)
	{
		mStartPos.x = x1;
		mStartPos.y = y1;
		mEndPos.x = x2;
		mEndPos.y = y2;
		//printf("Created line segment from %.0f,%.0f to %.0f,%.0f\n", x1, y1, x2, y2);
	};

	LineSegment(const raylib::Vector2& _pt1, const raylib::Vector2& _pt2)
		: mStartPos(_pt1)
		, mEndPos(_pt2)
	{
	};
	
	raylib::Vector2 mStartPos;
	raylib::Vector2 mEndPos;
};

#endif /* LineSegment_hpp */
