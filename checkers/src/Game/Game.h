#ifndef GAME_H
#define GAME_H

#include "../Checker/Checker.h"
#include "raylib.h"
#include <optional>
#include <vector>

using namespace std;

class Game
{
public:
  Game();
	void draw();
  vector<Checker> get_team_red();
  vector<Checker> get_team_blue();
  void remove_by_position(int x, int y);
  Vector2 listen_for_click();
  int get_round();
  void increment_round();
  optional<Checker> get_by_position(int x, int y);

private:
  void draw_board();
  void draw_pieces();
  vector<Checker> team_red;
  vector<Checker> team_blue;
  int round = 0;
};

#endif
