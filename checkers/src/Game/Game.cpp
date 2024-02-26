#include "Game.h"
#include "raylib.h"
#include <vector>

static const int SQUARE_SIZE = 100;
static const int EMPTY = 0;
static const int TEAM_RED = 1;
static const int TEAM_BLUE = 2;

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

// optional<Checker> Game::get_by_position(int x, int y)
// {
// 	return this->game[x - 1][y - 1];
// }

// void Game::remove(Checker checker)
// {
// 	vector<Checker>* team = (this->round % 2 == 0) ? &this->team_blue : &this->team_red;
// 	int x = checker.get_x();
// 	int y = checker.get_y();
//
// 	auto it = std::remove_if(team->begin(), team->end(), [x, y](Checker& checker) {
// 		return checker.get_x() == x && checker.get_y() == y;
// 	});
//
// 	team->erase(it, team->end());
// }

// void Game::moves(Checker checker)
// {
// 	cout << "Moves" << endl;
// }

// void Game::add_move(Vector2 move)
// {
// 	this->_moves.push_back(move);
// }

// void Game::reset_moves()
// {
// 	this->_moves.clear();
// }

// vector<Vector2> Game::get_moves()
// {
// 	return this->_moves;
// }
