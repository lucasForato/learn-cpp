#include "Game.h"
#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>

static const int SQUARE_SIZE = 100;
static const int EMPTY = 0;
static const int TEAM_RED = 1;
static const int TEAM_RED_KING = 3;
static const int TEAM_BLUE = 2;
static const int TEAM_BLUE_KING = 4;

// Constructor -----------------------------------------------------------------

Game::Game()
		: blue_score(0)
		, red_score(0)
		, round(0)
{
	for(int x = 0; x < 8; x++)
	{
		vector<int> row;
		for(int y = 0; y < 8; y++)
		{
			if(y < 3 && (y + x) % 2 == 0)
			{
				row.push_back(TEAM_BLUE);
			}
			else if(y > 4 && (y + x) % 2 == 0)
			{
				row.push_back(TEAM_RED);
			}
			else
			{
				row.push_back(EMPTY);
			}
		}
		game.push_back(row);
	}
}

// Drawing methods -------------------------------------------------------------

void Game::draw_board()
{
	vector<Vector2> moves = get_moves();
	optional<Vector2> focus = get_focus();

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if((i + j) % 2 == 0)
			{
				DrawRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
			}
			else
			{
				DrawRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RAYWHITE);
			}

			if(focus.has_value() && focus.value().x == i && focus.value().y == j)
			{
				DrawRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, YELLOW);
			}

			if(moves.size() > 0)
			{
				for(int k = 0; k < moves.size(); k++)
				{
					if(moves[k].x == i && moves[k].y == j)
					{
						DrawRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, GREEN);
					}
				}
			}
		}
	}
}

void Game::draw_score()
{
	DrawRectangle(800, 0, 200, 400, BLUE);
	DrawRectangle(800, 400, 200, 400, RED);
	string blue_score = "Score: " + to_string(this->blue_score);
	string red_score = "Score: " + to_string(this->red_score);

	DrawText(blue_score.c_str(), 820, 10, 30, BLACK);
	if(is_playing(TEAM_BLUE)) DrawText("PLAYING", 820, 60, 30, BLACK);

	DrawText(red_score.c_str(), 820, 410, 30, BLACK);
	if(is_playing(TEAM_RED)) DrawText("PLAYING", 820, 460, 30, BLACK);
}

void Game::draw_pieces()
{
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			int center_x = x * SQUARE_SIZE + SQUARE_SIZE / 2;
			int center_y = y * SQUARE_SIZE + SQUARE_SIZE / 2;
			int piece = game[x][y];
			if(piece == TEAM_RED) DrawCircle(center_x, center_y, 40, RED);
			if(piece == TEAM_BLUE) DrawCircle(center_x, center_y, 40, BLUE);
		}
	}
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	{
		draw_board();
		draw_pieces();
		draw_score();
	}
	EndDrawing();
}

// Game logic methods ----------------------------------------------------------

void Game::convert_position(Vector2& position)
{
	position.x = floor(position.x / SQUARE_SIZE);
	position.y = floor(position.y / SQUARE_SIZE);
}

Vector2 Game::get_board_position(float x, float y)
{
	x = floor(x / SQUARE_SIZE);
	y = floor(y / SQUARE_SIZE);
	return Vector2{x, y};
}

Vector2 Game::get_board_position(int x, int y)
{
	x = floor(x / SQUARE_SIZE);
	y = floor(y / SQUARE_SIZE);
	return Vector2{float(x), float(y)};
}

int Game::get_by_position(Vector2& position)
{
	return game[position.x][position.y];
}

void Game::remove_by_position(Vector2& position)
{
	game[position.x][position.y] = 0;
}

bool Game::can_move(DIRECTION direction, Vector2 position)
{
	int checker = 0;
	if(direction == TOP_LEFT)
	{
		go_top_left(position);
		if(is_invalid_position(position)) return false;
	}

	if(direction == TOP_RIGHT)
	{
		go_top_right(position);
		if(is_invalid_position(position)) return false;
	}

	if(direction == DOWN_LEFT)
	{
		go_down_left(position);
		if(is_invalid_position(position)) return false;
	}

	if(direction == DOWN_RIGHT)
	{
		go_down_right(position);
		if(is_invalid_position(position)) return false;
	}

	checker = get_by_position(position);
	return checker == EMPTY;
}

bool Game::can_conquer(DIRECTION direction, Vector2 position)
{
	int checker = 0;
	int team = get_by_position(position);

	if(team == EMPTY) return false;
	if(direction == TOP_LEFT)
	{
		go_top_left(position);
		int checker = get_by_position(position);
		if(checker == TEAM_BLUE || checker == TEAM_BLUE_KING)
		{
			go_top_left(position);
			if(is_invalid_position(position)) return false;
			return get_by_position(position) == EMPTY;
		}
	}

	if(direction == TOP_RIGHT)
	{
		go_top_right(position);
		int checker = get_by_position(position);
		if(checker == TEAM_BLUE || checker == TEAM_BLUE_KING)
		{
			go_top_right(position);
			if(is_invalid_position(position)) return false;
			return get_by_position(position) == EMPTY;
		}
	}

	if(direction == DOWN_LEFT)
	{
		go_down_left(position);
		int checker = get_by_position(position);
		if(checker == TEAM_RED || checker == TEAM_RED_KING)
		{
			go_down_left(position);
			if(is_invalid_position(position)) return false;
			return get_by_position(position) == EMPTY;
		}
	}

	if(direction == DOWN_RIGHT)
	{
		go_down_right(position);
		int checker = get_by_position(position);
		if(checker == TEAM_RED || checker == TEAM_RED_KING)
		{
			go_down_right(position);
			if(is_invalid_position(position)) return false;
			return get_by_position(position) == EMPTY;
		}
	}

	return false;
}

void Game::red_moves(Vector2& position)
{
	if(can_conquer(TOP_LEFT, position))
	{
		Vector2 position_1 = get_top_left(position);
		Vector2 position_2 = get_top_left(position, 2);
		add_move(position_1);
		add_move(position_2);
		return;
	}

	if(can_conquer(TOP_RIGHT, position))
	{
		Vector2 position_1 = get_top_right(position);
		Vector2 position_2 = get_top_right(position, 2);
		add_move(position_1);
		add_move(position_2);
		return;
	}

	if(can_move(TOP_LEFT, position))
	{
		Vector2 new_position = get_top_left(position);
		add_move(new_position);
	}

	if(can_move(TOP_RIGHT, position))
	{
		Vector2 new_position = get_top_right(position);
		add_move(new_position);
	}
}

void Game::blue_moves(Vector2& position)
{
	if(can_conquer(DOWN_LEFT, position))
	{
		Vector2 position_1 = get_down_left(position);
		Vector2 position_2 = get_down_left(position, 2);
		add_move(position_1);
		add_move(position_2);
		return;
	}

	if(can_conquer(DOWN_RIGHT, position))
	{
		Vector2 position_1 = get_down_right(position);
		Vector2 position_2 = get_down_right(position, 2);
		add_move(position_1);
		add_move(position_2);
		return;
	}

	if(can_move(DOWN_LEFT, position))
	{
		Vector2 new_position = get_down_left(position);
		add_move(new_position);
	}

	if(can_move(DOWN_RIGHT, position))
	{
		Vector2 new_position = get_down_right(position);
		add_move(new_position);
	}
}

void Game::red_king_moves(Vector2& position)
{
	cout << "Not implemented" << endl;
}

void Game::blue_king_moves(Vector2& position)
{
	cout << "Not implemented" << endl;
}

void Game::get_moves_by_position(Vector2& position)
{
	int checker = get_by_position(position);

	if(checker == TEAM_RED)
	{
	}

	if(checker == TEAM_RED) red_moves(position);
	if(checker == TEAM_BLUE) blue_moves(position);
	if(checker == TEAM_RED_KING) red_king_moves(position);
	if(checker == TEAM_BLUE_KING) blue_king_moves(position);
	if(moves.size()) set_focus(position);
}

vector<Vector2> Game::get_moves()
{
	return moves;
}

void Game::reset_moves()
{
	moves.clear();
}

void Game::add_move(Vector2 position)
{
	moves.push_back(position);
}

optional<Vector2> Game::get_focus()
{
	return focus;
}

void Game::reset_focus()
{
	focus = nullopt;
}

void Game::set_focus(Vector2& new_focus)
{
	focus = new_focus;
}

bool Game::is_invalid_position(Vector2& position)
{
	return position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7;
}

bool Game::is_valid_move(Vector2& position)
{
	for(int i = 0; i < moves.size(); i++)
	{
		if(moves[i].x == position.x && moves[i].y == position.y) return true;
	}
	return false;
}

void Game::move_checker(Vector2& from, Vector2& to)
{
	int checker = game[from.x][from.y];
	game[from.x][from.y] = EMPTY;
	game[to.x][to.y] = checker;
}

void Game::increment_score(int& team)
{
	if(team == TEAM_RED) red_score++;
	if(team == TEAM_BLUE) blue_score++;
}

void Game::next_round()
{
	round++;
}

bool Game::is_playing(const int& team)
{
	if(round % 2 == 0 && team == TEAM_RED) return true;
	if(round % 2 != 0 && team == TEAM_BLUE) return true;
	return false;
}

void Game::go_top_left(Vector2& p, int i)
{
	p.x -= i;
	p.y -= i;
}

void Game::go_top_right(Vector2& p, int i)
{
	p.x += i;
	p.y -= i;
}

void Game::go_down_left(Vector2& p, int i)
{
	p.x -= i;
	p.y += i;
}

void Game::go_down_right(Vector2& p, int i)
{
	p.x += i;
	p.y += i;
}

Vector2 Game::get_top_left(Vector2 p, int i)
{
	p.x -= i;
	p.y -= i;
	return p;
}

Vector2 Game::get_top_right(Vector2 p, int i)
{
	p.x += i;
	p.y -= i;
	return p;
}

Vector2 Game::get_down_left(Vector2 p, int i)
{
	p.x -= i;
	p.y += i;
	return p;
}

Vector2 Game::get_down_right(Vector2 p, int i)
{
	p.x += i;
	p.y += i;
	return p;
}
