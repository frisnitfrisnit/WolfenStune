//
//  Player.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Player.hpp"
#include "Game.hpp"
#include "raylib-cpp.hpp"

void Player::Init(int _x, int _y)
{
	mPos = raylib::Vector2(_x, _y);
}

void Player::UpdatePlayer(float _ts)
{
	// Move
	if(IsKeyDown(KEY_W))
	{
		raylib::Vector2 dir(1.0f, 0.0f);
		dir = dir.Rotate(RAD2DEG * mAngle);
		raylib::Vector2 newPos;
		newPos = mPos + (dir * mMoveSpeed);
		if(!Game::GetMap().IsWallAtPos(newPos))
			mPos = newPos;
	}
	else if(IsKeyDown(KEY_S))
	{
		raylib::Vector2 dir(1.0f, 0.0f);
		dir = dir.Rotate(RAD2DEG * mAngle);
		raylib::Vector2 newPos;
		newPos = mPos + (dir * -mMoveSpeed);
		if(!Game::GetMap().IsWallAtPos(newPos))
			mPos = newPos;
	}

	// Rotate
	if(IsKeyDown(KEY_D))
	{
		mAngle += mRotationSpeed;
	}
	else if(IsKeyDown(KEY_A))
	{
		mAngle -= mRotationSpeed;
	}
}

void Player::DrawPlayer()
{
	DrawCircleV(mPos, mRadius, RED);
	raylib::Vector2 dir(1.0f, 0.0f);
	dir = dir.Rotate(RAD2DEG * mAngle);
	raylib::Vector2 endPos = mPos + (dir * 30.0f);
	DrawLineV(mPos, endPos, RED);
}
