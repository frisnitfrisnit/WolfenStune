//
//  Player.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include "raylib-cpp.hpp"

class Player
{
public:
	Player() {}
	
	void Init(int _x, int _y);
	void UpdatePlayer(float _ts);
	void DrawPlayer();
	
	raylib::Vector2 mPos;
	int mRadius = 3;
	float mAngle = 0.0f;
	float mMoveSpeed = 2.0f;
	float mRotationSpeed = 2 * DEG2RAD;
};

#endif /* Player_hpp */
