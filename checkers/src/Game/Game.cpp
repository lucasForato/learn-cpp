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
		this->game.push_back(row);
	}
}

// Drawing methods -------------------------------------------------------------

void Game::draw_board()
{
	vector<Vector2> moves = this->get_moves();
	optional<Vector2> focus = this->get_focus();

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

void Game::draw_pieces()
{
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			int center_x = x * SQUARE_SIZE + SQUARE_SIZE / 2;
			int center_y = y * SQUARE_SIZE + SQUARE_SIZE / 2;
			int piece = this->game[x][y];
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
		this->draw_board();
		this->draw_pieces();
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
	return this->game[position.x][position.y];
}

void Game::remove_by_position(Vector2& position)
{
	this->game[position.x][position.y] = 0;
}

bool Game::can_move(DIRECTION direction, Vector2 position)
{
	int checker = 0;
	if(direction == TOP_LEFT)
	{
		position.x -= 1;
		position.y -= 1;
		if(is_invalid_position(position)) return false;
	}

	if(direction == TOP_RIGHT)
	{
		position.x += 1;
		position.y -= 1;
		if(is_invalid_position(position)) return false;
	}

	checker = get_by_position(position);
	return checker == EMPTY;
}

bool Game::can_conquer(DIRECTION direction, Vector2 position)
{
	int checker = 0;
	int team = get_by_position(position);

	if(direction == TOP_LEFT)
	{
		position.x -= 1;
		position.y += 1;
		if(is_invalid_position(position)) return false;

		checker = get_by_position(position);
		if((team == TEAM_RED && checker == TEAM_BLUE) || (team == TEAM_BLUE && checker == TEAM_RED))
		{
			position.x -= 1;
			position.y += 1;

			if(is_invalid_position(position)) return false;
			checker = get_by_position(position);
			return checker == EMPTY;
		}
	}

	return false;
}

void Game::red_moves(Vector2& position)
{
	if(can_conquer(TOP_LEFT, position))
	{
		add_move(Vector2{position.x - 2, position.y + 2});
		return;
	}

	if(can_conquer(TOP_RIGHT, position))
	{
		add_move(Vector2{position.x - 2, position.y + 2});
		return;
	}

	if(can_move(TOP_LEFT, position))
	{
		add_move(Vector2{position.x - 1, position.y - 1});
	}

	if(can_move(TOP_RIGHT, position))
	{
		add_move(Vector2{position.x + 1, position.y - 1});
	}
}

void Game::blue_moves(Vector2& position)
{
	cout << "Not implemented" << endl;
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
	int checker = this->game[position.x][position.y];

	if(checker == TEAM_RED) red_moves(position);
	if(checker == TEAM_BLUE) blue_moves(position);
	if(checker == TEAM_RED_KING) red_king_moves(position);
	if(checker == TEAM_BLUE_KING) blue_king_moves(position);

	if(this->moves.size() > 0) set_focus(position);
}

vector<Vector2> Game::get_moves()
{
	return this->moves;
}

void Game::reset_moves()
{
	this->moves.clear();
}

void Game::add_move(Vector2 position)
{
	this->moves.push_back(position);
}

optional<Vector2> Game::get_focus()
{
	return this->focus;
}

void Game::reset_focus()
{
	this->focus = nullopt;
}

void Game::set_focus(Vector2& new_focus)
{
	this->focus = new_focus;
}

bool Game::is_invalid_position(Vector2& position)
{
	return position.x < 0 || position.x > 7 || position.y < 0 || position.y > 7;
}
