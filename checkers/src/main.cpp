#include "Game/Game.h"
#include "raylib.h"

int main(void)
{
	InitWindow(800, 800, "Checkers");

	while(!WindowShouldClose())
	{
		
    Game game = Game();
		game.draw();
	}

	CloseWindow();

	return 0;
}
