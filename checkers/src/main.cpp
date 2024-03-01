#include "EventManager/EventManager.h"
#include "Game/Game.h"
#include "raylib.h"

using namespace std;

int main(void)
{
	InitWindow(1000, 800, "Checkers");
	Game game = Game();

	while(!WindowShouldClose())
	{
		EventManager::connect(EventManager::CLICK(), [&game]() {
			if(game.get_focus().has_value())
			{
				Vector2 position = Game::get_board_position(GetTouchX(), GetTouchY());
				if(game.is_valid_move(position))
				{
					Vector2 focus = game.get_focus().value();
					game.move_checker(focus, position);
				  game.next_round();
				}
				game.reset_moves();
				game.reset_focus();
			}
			else
			{
				Vector2 position = Game::get_board_position(GetTouchX(), GetTouchY());
				int checker = game.get_by_position(position);
				if(game.is_playing(checker))
				{
					game.reset_moves();
					game.reset_focus();
					game.get_moves_by_position(position);
				}
			}
		});

		game.draw();
	}

	CloseWindow();

	return 0;
}
