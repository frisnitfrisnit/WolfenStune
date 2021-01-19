#include "raylib-cpp.hpp"
#include "Game.hpp"

const int sMapTileSize = 57;

int main() {
		// Initialization
		//--------------------------------------------------------------------------------------
		int screenWidth = 15 * sMapTileSize;
		int screenHeight = 11 * sMapTileSize;
		raylib::Window w(screenWidth, screenHeight, "WolfenStune");
		SetTargetFPS(60);
	
		Game::InitGame(screenWidth, screenHeight, sMapTileSize);

		//--------------------------------------------------------------------------------------

		// Main game loop
		while (!w.ShouldClose())    // Detect window close button or ESC key
		{
			Game::UpdateGame(GetFrameTime());

			// Draw
			//----------------------------------------------------------------------------------
			BeginDrawing();
			ClearBackground(BLACK);
			Game::RenderGame();
			EndDrawing();
			//----------------------------------------------------------------------------------
		}

		return 0;
}

