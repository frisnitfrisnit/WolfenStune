//
//  Ray2d.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 14/01/2021.
//

#include "Ray2d.hpp"
#include "Game.hpp"



Ray2d::Ray2d(const raylib::Vector2& _pos, const float _angle)
{
	mPos = _pos;
	mAngle = NormalizeAngle(_angle);
	mWasHitVertical = false;
	
	isRayFacingDown = mAngle > 0 && mAngle < PI;
	isRayFacingUp = !isRayFacingDown;

	isRayFacingRight = mAngle < 0.5 * PI || mAngle > 1.5 * PI;
	isRayFacingLeft = !isRayFacingRight;
}

float Ray2d::NormalizeAngle(const float _angle) const
{
		float angleNorm = fmodf(_angle, 2.0f * PI);
		if (angleNorm < 0.0f)
		{
			angleNorm += 2.0f * PI;
		}
		return angleNorm;
}

bool Ray2d::Cast()
{
	const Map& map(Game::mMap);

	// Check horizontal intersections
	float xIntercept, yIntercept;
	float xStep, yStep;
	float distanceH = MAXFLOAT;
	const float tileSize(map.mTileSize);
	
	float horizTouchX = MAXFLOAT;
	float horizTouchY = MAXFLOAT;
	if(mAngle != 0 && mAngle != PI) // tan of these is undefined so skip them (will be picked up by Vert check)
	{
		// Find the coordinates of the closest horizontal grid intersections
		yIntercept = floorf(mPos.y / tileSize) * tileSize;
		yIntercept += isRayFacingDown ? tileSize : 0; // Checking next tile down if facing down
		xIntercept = mPos.x + ((yIntercept - mPos.y) / tan(mAngle));

		// Calculate the step
		yStep = tileSize * (isRayFacingUp ? -1 : 1);
		xStep = tileSize / tan(mAngle);
		// Invert the step if the direction is flipped
		// TODO: Isn't there a better/clearer way of doing this?
		xStep *= (isRayFacingLeft && xStep > 0.0f) ? -1 : 1;
		xStep *= (isRayFacingRight && xStep < 0.0f) ? -1 : 1;

		horizTouchX = xIntercept;
		horizTouchY = yIntercept;
		while(horizTouchX >= 0 && horizTouchX <= Game::mScreenWidth &&
					horizTouchY >= 0 && horizTouchY <= Game::mScreenHeight)
		{
			if(map.IsWallAtPos(horizTouchX, horizTouchY - (isRayFacingUp ? 1 : 0)))
			{
				distanceH = mPos.Distance(raylib::Vector2(horizTouchX, horizTouchY));
				break;
			}
			horizTouchX += xStep;
			horizTouchY += yStep;
		}
	}
	
	// Check vertical intersection
	float distanceV = MAXFLOAT;
	float vertTouchX = MAXFLOAT;
	float vertTouchY = MAXFLOAT;
	// Find the coordinates of the closest vertical grid intersections
	xIntercept = floorf(mPos.x / tileSize) * tileSize;
	xIntercept += isRayFacingRight ? tileSize : 0; // Checking next tile across if facing right
	yIntercept = mPos.y + ((xIntercept - mPos.x) * tan(mAngle));
	
	xStep = tileSize * (isRayFacingLeft ? -1 : 1);
	yStep = tileSize * tan(mAngle);
	// Invert the step if the direction is flipped
	// TODO: Isn't there a better/clearer way of doing this?
	yStep *= (isRayFacingUp && yStep > 0.0f) ? -1 : 1;
	yStep *= (isRayFacingDown && yStep < 0.0f) ? -1 : 1;
	
	vertTouchX = xIntercept;
	vertTouchY = yIntercept;
	while(vertTouchX >= 0 && vertTouchX <= Game::mScreenWidth &&
				vertTouchY >= 0 && vertTouchY <= Game::mScreenHeight)
	{
		if(map.IsWallAtPos(vertTouchX - (isRayFacingLeft ? 1 : 0), vertTouchY))
		{
			distanceV = mPos.Distance(raylib::Vector2(vertTouchX, vertTouchY));
			break;
		}
		vertTouchX += xStep;
		vertTouchY += yStep;
	}
	
	mLength = fmin(distanceH, distanceV);
	mWasHitVertical = distanceV < distanceH;
	distanceH < distanceV ? mIntersection = raylib::Vector2(horizTouchX, horizTouchY) :
													mIntersection = raylib::Vector2(vertTouchX, vertTouchY);

	return true;
}
