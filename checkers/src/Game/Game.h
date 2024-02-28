#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <optional>
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
	void draw();
	void next_round();
	int get_by_position(Vector2&);
	void remove_by_position(Vector2&);
	void get_moves_by_position(Vector2&);
	vector<Vector2> get_moves();
	void reset_moves();
	void add_move(Vector2);
	optional<Vector2> get_focus();
	void reset_focus();
	void set_focus(Vector2&);
	bool is_invalid_position(Vector2&);
	static void convert_position(Vector2&);
	static Vector2 get_board_position(int x, int y);
	static Vector2 get_board_position(float x, float y);

	private:
	void red_moves(Vector2&);
	void blue_moves(Vector2&);
	void red_king_moves(Vector2&);
	void blue_king_moves(Vector2&);

	bool can_move(DIRECTION, Vector2);
	bool can_conquer(DIRECTION, Vector2);

	void draw_board();

	void draw_pieces();
	vector<vector<int>> game;
	vector<Vector2> moves;
	optional<Vector2> focus;
};

#endif
