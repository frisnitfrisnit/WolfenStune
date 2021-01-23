//
//  Game.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Game.hpp"

// TODO: Look at the atan method, as I *think* that's why I'm getting a hole at 90 (doesn't explain doubling at -90), unless there's a ray crossover or floating point accuracy issue, as I can't see it with 5x as many rays?

int Game::mScreenWidth;
int Game::mScreenHeight;

Map Game::mMap;
Player Game::mPlayer;
float Game::mMiniMapScaleFactor = 0.2f;


void Game::InitGame(const int _screenWidth, const int _screenHeight, const int _mapTileSize)
{
	mScreenWidth = _screenWidth;
	mScreenHeight = _screenHeight;
	
	mMap.CreateMap(_mapTileSize);
	mPlayer.Init(Game::mScreenWidth / 2, Game::mScreenHeight / 2);
}

void Game::UpdateGame(const float _ts)
{
	mPlayer.UpdatePlayer(_ts);
}

void Game::RenderGame()
{
	mMap.DrawMap();
	mPlayer.DrawPlayer();
}
