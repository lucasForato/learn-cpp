#ifndef GAME_H
#define GAME_H

#include "../Checker/Checker.h"
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

private:
  void draw_board();
  void draw_pieces();

  vector<Checker> team_red;
  vector<Checker> team_blue;

  // update the game state
  // check winner
  // hold team_red pieces and placements
  // hold team_blue pieces and placements
  // hold winner
};

#endif
