#include "Game.h"
#include "raylib.h"
#include <iostream>
#include <vector>

static const int SQUARE_SIZE = 100;

static const int EMPTY = 0;

static const int TEAM_RED = 1;
static const int TEAM_RED_KING = 3;

static const int TEAM_BLUE = 2;
static const int TEAM_BLUE_KING = 4;

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

void Game::draw_board()
{
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
		}
	}
}

void Game::draw_board(vector<Vector2>& position)
{
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
			if(piece == TEAM_RED)
				DrawCircle(center_x, center_y, 40, RED);
			if(piece == TEAM_BLUE)
				DrawCircle(center_x, center_y, 40, BLUE);
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

void Game::draw(vector<Vector2>& positions)
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	{
		this->draw_board(positions);
		this->draw_pieces();
	}
	EndDrawing();
}

void Game::convert_position(Vector2& position)
{
	position.x = position.x / SQUARE_SIZE;
	position.y = position.y / SQUARE_SIZE;
}

int Game::get_by_position(Vector2& position)
{
	convert_position(position);
	return this->game[position.x][position.y];
}

void Game::remove_by_position(Vector2& position)
{
	convert_position(position);
	this->game[position.x][position.y] = 0;
}

bool Game::can_move(DIRECTION direction, Vector2& position)
{
	int result = 0;
	if(direction == TOP_LEFT)
	{
		position.x -= 1;
		position.y += 1;
		result = get_by_position(position);
	}
	else if(direction == TOP_RIGHT)
	{
		position.x += 1;
		position.y += 1;
		result = get_by_position(position);
	}
	else if(direction == DOWN_RIGHT)
	{
		position.x -= 1;
		position.y -= 1;
		result = get_by_position(position);
	}
	else if(direction == DOWN_LEFT)
	{
		position.x += 1;
		position.y -= 1;
		result = get_by_position(position);
	}

	return result == EMPTY;
}

bool Game::can_conquer(DIRECTION direction, Vector2& position)
{
	int result = 0;
	int team = get_by_position(position);

	// top left
	if(direction == TOP_LEFT)
	{
		position.x -= 1;
		position.y += 1;
		result = get_by_position(position);
		if((team == TEAM_RED && result == TEAM_BLUE) || (team == TEAM_BLUE && result == TEAM_RED))
		{
			position.x -= 1;
			position.y += 1;
			result = get_by_position(position);
			return result == EMPTY;
		}
		return false;
	}
	// top right
	else if(direction == TOP_RIGHT)
	{
		position.x += 1;
		position.y += 1;
		result = get_by_position(position);
		if((team == TEAM_RED && result == TEAM_BLUE) || (team == TEAM_BLUE && result == TEAM_RED))
		{
			position.x += 1;
			position.y += 1;
			result = get_by_position(position);
			return result == EMPTY;
		}
		return false;
	}
	// down left
	else if(direction == DOWN_RIGHT)
	{
		position.x -= 1;
		position.y -= 1;
		result = get_by_position(position);
		if((team == TEAM_RED && result == TEAM_BLUE) || (team == TEAM_BLUE && result == TEAM_RED))
		{
			position.x -= 1;
			position.y -= 1;
			result = get_by_position(position);
			return result == EMPTY;
		}
		return false;
	}
	// down right
	else if(direction == DOWN_LEFT)
	{
		position.x += 1;
		position.y -= 1;
		result = get_by_position(position);
		if((team == TEAM_RED && result == TEAM_BLUE) || (team == TEAM_BLUE && result == TEAM_RED))
		{
			position.x += 1;
			position.y -= 1;
			result = get_by_position(position);
			return result == EMPTY;
		}
		return false;
	}
}

void Game::red_moves(vector<Vector2>& moves, Vector2& position)
{
	cout << "Not implemented" << endl;
	bool can_move_checker = false;
	bool can_conquer_checker = false;

	if(can_conquer(TOP_LEFT, position))
	{
		moves.push_back(Vector2{position.x - 2, position.y + 2});
	}
	if(can_conquer(TOP_RIGHT, position))
	{
    moves.push_back(Vector2{position.x - 2, position.y - 2});
	}
	if(can_move(TOP_LEFT, position))
	{
		moves.push_back(Vector2{position.x - 2, position.y + 2});
	}
	if(can_move(TOP_RIGHT, position))
	{
    moves.push_back(Vector2{position.x - 2, position.y - 2});
	}
}

void Game::blue_moves(vector<Vector2>& moves, Vector2& position)
{
	cout << "Not implemented" << endl;
}

void Game::king_moves(vector<Vector2>& moves, Vector2& position)
{
	cout << "Not implemented" << endl;
}

vector<Vector2> Game::get_moves_by_position(Vector2& position)
{
	convert_position(position);
	int checker = this->game[position.x][position.y];

	vector<Vector2> moves;
	if(checker == TEAM_RED)
	{
		red_moves(moves, position);
	}

	else if(checker == TEAM_BLUE)
	{
		blue_moves(moves, position);
	}

	else if(checker == TEAM_RED_KING || checker == TEAM_BLUE_KING)
	{
		king_moves(moves, position);
	}

	return moves;
}
