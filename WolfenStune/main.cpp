#include "raylib-cpp.hpp"
#include "Game.hpp"

int main() {
		// Initialization
		//--------------------------------------------------------------------------------------
		int screenWidth = 15 * 32;
		int screenHeight = 11 * 32;
		raylib::Window w(screenWidth, screenHeight, "WolfenStune");
		SetTargetFPS(60);
	
		Game::InitGame(screenWidth, screenHeight);

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

