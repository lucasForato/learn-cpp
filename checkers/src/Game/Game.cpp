#include "Game.h"
#include "../Checker/Checker.h"
#include "raylib.h"
#include <vector>

static const int square_size = 100;

Game::Game()
{
	vector<Checker> team_red;
	vector<Checker> team_blue;
	int x = 0;
	int y = 0;
	while(team_red.size() <= 13)
	{
		team_red.push_back(Checker(x, y));
		if(x > 7 && y == 0)
		{
			++y;
			x = 1;
		}
		else if(x > 7 && y == 1)
		{
			++y;
			x = 0;
		}
		else
		{
			x += 2;
		}
	}

	x = 7;
	y = 7;
	while(team_blue.size() <= 13)
	{
		team_blue.push_back(Checker(x, y));
		if(x < 0 && y == 7)
		{
			--y;
			x = 6;
		}
		else if(x < 0 && y == 6)
		{
			--y;
			x = 7;
		}
		else
		{
			x -= 2;
		}
	}
	this->team_red = team_red;
	this->team_blue = team_blue;
}

void Game::draw_board()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if((i + j) % 2 == 0)
			{
				DrawRectangle(i * square_size, j * square_size, square_size, square_size, BLACK);
			}
			else
			{
				DrawRectangle(i * square_size, j * square_size, square_size, square_size, RAYWHITE);
			}
		}
	}
}

void Game::draw_pieces()
{
	for(auto& checker : this->team_red)
	{
		int x = (checker.get_x() * 100) + 50;
		int y = (checker.get_y() * 100) + 50;
		DrawCircle(x, y, 40, RED);
	}

	for(auto& checker : this->team_blue)
	{
		int x = (checker.get_x() * 100) + 50;
		int y = (checker.get_y() * 100) + 50;
		DrawCircle(x, y, 40, BLUE);
	}
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	this->draw_board();
	this->draw_pieces();
	EndDrawing();
}
