#ifndef GAME_H
#define GAME_H

#include "../Checker/Checker.h"
#include "raylib.h"
#include <vector>

using namespace std;

class Game
{
public:
	Game();
	void draw();

	TEAM get_playing_team();
	void next_round();
	int get_by_position(int x, int y);

private:
	void draw_board();
	void draw_pieces();
  vector<vector<int>> game;
};

#endif
