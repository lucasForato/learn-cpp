#include "EventManager/EventManager.h"
#include "Game/Game.h"
#include "raylib.h"

using namespace std;

int main(void)
{
	InitWindow(800, 800, "Checkers");
	Game game = Game();
	EventManager event_manager;

	while(!WindowShouldClose())
	{
    vector<Vector2> moves;
		event_manager.connect(EventManager::CLICK(), [&game, &moves]() {
			Vector2 position = Vector2{float(GetTouchX()), float(GetTouchY())};
      moves = game.get_moves_by_position(position);
		});

    if (moves.size() > 0)
    {
      game.draw(moves);
    }
    else
    {
      game.draw();
    }
	}

	CloseWindow();

	return 0;
}
