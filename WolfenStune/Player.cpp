//
//  Player.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Player.hpp"
#include "Game.hpp"
#include <stdio.h>

//#define SINGLE_RAY

static const Color sRayColour{255, 0, 255, 40};
static const int sRayDisplayWidth = 1;

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
	mNumRays = Game::mScreenWidth / Game::mMap.mWallWidth;
}

void Player::UpdatePlayer(float _ts)
{
	// Move
	if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
	{
		raylib::Vector2 newPos;
		newPos = mPos + (GetPlayerDir() * mMoveSpeed);
		if(!Game::GetMap().IsWallAtPosV(newPos))
			mPos = newPos;
	}
	else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
	{
		raylib::Vector2 newPos;
		newPos = mPos + (GetPlayerDir() * -mMoveSpeed);
		if(!Game::GetMap().IsWallAtPosV(newPos))
			mPos = newPos;
	}

	// Rotate
	if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
		mAngle += mRotationSpeed;
	}
	else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{
		mAngle -= mRotationSpeed;
	}
	
	// Cast rays to walls
	// TODO: This should only happen when an update is needed
	// TODO: Precache the rays rather than recreating?
	mWallRays.clear();
#ifdef SINGLE_RAY
	Ray2d newRay(mPos, mAngle);
	newRay.Cast();
	mWallRays.push_back(newRay);
#else
	float rayAngle = mAngle - (mFOVAngle / 2.0f);
	for(int col = 0; col < mNumRays; col++)
	{
		Ray2d newRay(mPos, rayAngle);
		newRay.Cast();
		mWallRays.push_back(newRay);
		//printf("NewRay @ %.2f\n", rayAngle * RAD2DEG);
		rayAngle += mFOVAngle / mNumRays;
	}
#endif
}

void Player::DrawPlayer()
{
	const float scale = Game::mMiniMapScaleFactor;
	// Draw rays below player
	for(auto& r:mWallRays)
	{
#ifdef SINGLE_RAY
		char rayPosText[32];
		sprintf(rayPosText, "%d,%d", (int)r.mPos.x, (int)r.mPos.y);
		DrawText(rayPosText, 10, 10, 16, WHITE);
#endif
		
		raylib::Vector2 rayDir = Vector2Rotate(Vector2{1.0f, 0.0f}, r.mAngle * RAD2DEG);
		raylib::Vector2 endPos = r.mPos + (rayDir * r.mLength);
		DrawCircleLines(r.mIntersection.x * scale, r.mIntersection.y * scale, 3 * scale, BLUE);
		DrawLineEx(r.mPos * scale, endPos * scale, sRayDisplayWidth, sRayColour);
	}

	DrawCircleV(mPos * scale, mRadius * scale, RED);
	// Dir
	raylib::Vector2 endPos = mPos + (GetPlayerDir() * 30.0f);
	DrawLineV(mPos * scale, endPos * scale, BLUE);
}

raylib::Vector2 Player::GetPlayerDir() const
{
	raylib::Vector2 dir(1.0f, 0.0f);
	dir = dir.Rotate(RAD2DEG * mAngle);
	return dir;
}
