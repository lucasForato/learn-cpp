#include "EventManager/EventManager.h"
#include "Game/Game.h"
#include "raylib.h"
// #include <iostream>

int main(void)
{
	InitWindow(800, 800, "Checkers");

	while(!WindowShouldClose())
	{

		Game game = Game();
		EventManager event_manager;

		event_manager.connect(EventManager::CLICK(), [&game]() {
			float x = GetTouchX();
			float y = GetTouchY();
			Vector2 click = {x, y};
      optional<Checker> res = game.get_by_position(click.x, click.y);
		});

		game.draw();
	}

	CloseWindow();

	return 0;
}
