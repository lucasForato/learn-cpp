
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <optional>
#include <vector>

using namespace std;

enum DIRECTION
{
	TOP_LEFT,
	TOP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

class Game
{
	public:
	// Constructors and destructors
	Game();

	// Public member functions
	void draw();
	void draw_score();
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
	bool is_valid_move(Vector2&);
	void move_checker(Vector2&, Vector2&);
	void increment_score(int&);
	bool is_playing(const int&);

	private:
	// Private member functions
	void red_moves(Vector2&);
	void blue_moves(Vector2&);
	void red_king_moves(Vector2&);
	void blue_king_moves(Vector2&);
	bool can_move(DIRECTION, Vector2);
	bool can_conquer(DIRECTION, Vector2);
	void draw_board();
	void draw_pieces();

	static void go_top_left(Vector2&, int = 1);
	static Vector2 get_top_left(Vector2, int = 1);

	static void go_top_right(Vector2&, int = 1);
	static Vector2 get_top_right(Vector2, int = 1);

	static void go_down_left(Vector2&, int = 1);
	static Vector2 get_down_left(Vector2, int = 1);

	static void go_down_right(Vector2&, int = 1);
	static Vector2 get_down_right(Vector2, int = 1);

	// Private member variables
	vector<vector<int>> game;
	vector<Vector2> moves;
	optional<Vector2> focus;
	int blue_score;
	int red_score;
	int round;
};

#endif
