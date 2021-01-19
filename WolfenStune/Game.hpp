//
//  Game.hpp
//  WolfenStune
//
//  Created by Stuart Hunt on 12/01/2021.
//

#ifndef Game_h
#define Game_h

#include "Map.hpp"
#include "Player.hpp"

class Game
{
public:
	static void InitGame(const int _screenWidth, const int _screenHeight, const int _mapTileSize);
	static void UpdateGame(const float _ts);
	static void RenderGame();
	
	static const Map& GetMap() { return mMap; }
	static const Player& GetPlayer() { return mPlayer; }
		
	static int mScreenWidth;
	static int mScreenHeight;
		
	static Map mMap;
	static Player mPlayer;

};

#endif /* Game_h */
