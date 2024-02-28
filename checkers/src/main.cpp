#include "EventManager/EventManager.h"
#include "Game/Game.h"
#include "raylib.h"
#include <iostream>

using namespace std;

int main(void)
{
	InitWindow(800, 800, "Checkers");
	Game game = Game();

	while(!WindowShouldClose())
	{
		EventManager::connect(EventManager::CLICK(), [&game]() {
			Vector2 position = Game::get_board_position(GetTouchX(), GetTouchY());
			game.reset_moves();
			game.reset_focus();
			game.get_moves_by_position(position);
			cout << "moves: " << game.get_moves().size() << endl;
		});

		game.draw();
	}

	CloseWindow();

	return 0;
}
