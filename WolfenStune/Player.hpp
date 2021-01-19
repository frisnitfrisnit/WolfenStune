//
//  Player.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include "raylib-cpp.hpp"
#include "Ray2d.hpp"
#include <vector>

class Player
{
public:
	Player();
	virtual ~Player();
	
	void Init(int _x, int _y);
	void UpdatePlayer(float _ts);
	void DrawPlayer();
	
	raylib::Vector2 GetPlayerDir() const;
	
	raylib::Vector2 mPos;
	int mRadius = 3;
	float mAngle = 0.0f;//315 * DEG2RAD;
	float mMoveSpeed = 2.0f;
	float mRotationSpeed = 2 * DEG2RAD;
	
	float mFOVAngle;
	float mNumRays = 0;

	std::vector<Ray2d> mWallRays;
};

#endif /* Player_hpp */
