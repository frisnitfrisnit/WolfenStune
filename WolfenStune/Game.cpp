//
//  Game.cpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#include "Game.hpp"

int Game::mScreenWidth;
int Game::mScreenHeight;

Map Game::mMap;
Player Game::mPlayer;

void Game::InitGame(const int screenWidth, const int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	
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
