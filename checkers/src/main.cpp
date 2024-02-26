#include "EventManager/EventManager.h"
#include "Game/Game.h"
#include "raylib.h"
#include <iostream>

using namespace std;

int main(void)
{
	InitWindow(800, 800, "Checkers");
	Game game = Game();
	EventManager event_manager;

	while(!WindowShouldClose())
	{
		// event_manager.connect(EventManager::CLICK(), [&game]() {
		// 	float x = GetTouchX();
		// 	float y = GetTouchY();
		// 	Vector2 click = {x, y};
  //     cout << "Click at " << x << ", " << y << endl;
		// 	// optional<Checker> checker = game.get_by_position(click.x, click.y);
		// });

		game.draw();
	}

	CloseWindow();

	return 0;
}
