//
//  Player.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Player.hpp"
#include "Game.hpp"

static const float sMaxRayLength = 100.0f;
static const Color sRayColour{0, 255, 0, 80};
static const int sWallWidth = 5;

Player::Player()
{
}

Player::~Player()
{
	mWallRays.clear();
}

void Player::Init(int _x, int _y)
{
	mPos = raylib::Vector2(_x, _y);
	mFOVAngle = 60 * DEG2RAD;
	mNumRays = Game::mScreenWidth / sWallWidth;
}

void Player::UpdatePlayer(float _ts)
{
	// Move
	if(IsKeyDown(KEY_W))
	{
		raylib::Vector2 newPos;
		newPos = mPos + (GetPlayerDir() * mMoveSpeed);
		if(!Game::GetMap().IsWallAtPos(newPos))
			mPos = newPos;
	}
	else if(IsKeyDown(KEY_S))
	{
		raylib::Vector2 newPos;
		newPos = mPos + (GetPlayerDir() * -mMoveSpeed);
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
	
	// Cast rays to walls
	// TODO: This should only happen when an update is needed
	// TODO: Precache the rays rather than recreating?
	mWallRays.clear();
	float rayAngle = mAngle - (mFOVAngle / 2.0f);
	for(int r=0; r<mNumRays; r++)
	{
		Ray2d newRay(mPos, rayAngle);
		mWallRays.push_back(newRay);
		//printf("NewRay @ %.2f\n", rayAngle * RAD2DEG);
		rayAngle += mFOVAngle / mNumRays;
	}
}

void Player::DrawPlayer()
{
	// Draw rays below player
	for(auto& r:mWallRays)
	{
		raylib::Vector2 rayDir = Vector2Rotate(Vector2{1.0f, 0.0f}, r.mAngle * RAD2DEG);
		raylib::Vector2 endPos = r.mPos + (rayDir * sMaxRayLength);
		//printf("From %.2f,%.2f to %.2f,%.2f\n", r.mPos.x, r.mPos.y, tmp.x, tmp.y);
		DrawLineV(r.mPos, endPos, sRayColour);
	}

	DrawCircleV(mPos, mRadius, RED);
	raylib::Vector2 endPos = mPos + (GetPlayerDir() * 30.0f);
	DrawLineV(mPos, endPos, RED);
}

raylib::Vector2 Player::GetPlayerDir() const
{
	raylib::Vector2 dir(1.0f, 0.0f);
	dir = dir.Rotate(RAD2DEG * mAngle);
	return dir;
}
