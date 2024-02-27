#ifndef GAME_H
#define GAME_H

#include "../Checker/Checker.h"
#include "raylib.h"
#include <vector>

using namespace std;

enum DIRECTION
{
	TOP_LEFT = 0,
	TOP_RIGHT = 1,
	DOWN_LEFT = 2,
	DOWN_RIGHT = 3
};

class Game
{
public:
	Game();
	void draw(vector<Vector2>&);
	void draw();

	TEAM get_playing_team();
	void next_round();
	int get_by_position(Vector2&);
	void remove_by_position(Vector2&);
  vector<Vector2> get_moves_by_position(Vector2&);

private:
  void red_moves(vector<Vector2>&, Vector2&); 
  void blue_moves(vector<Vector2>&, Vector2&); 
  void king_moves(vector<Vector2>&, Vector2&);

  bool can_move(DIRECTION, Vector2&);
  bool can_conquer(DIRECTION, Vector2&);

	void draw_board();
	void draw_board(vector<Vector2>&);

	void draw_pieces();
	void convert_position(Vector2&);
	vector<vector<int>> game;
};

#endif
