#include "Checker.h"
#include "raylib.h"

const int SQUARE_SIZE = 100;

Checker::Checker(int x, int y, TEAM team)
	: x{x}
	, y{y}
	, is_king{false}
	, team{team}
{ }

void Checker::set_x(int x)
{
	if(x >= 0 && x < 8)
		this->x = x;
}

int Checker::get_x()
{
	return this->x;
}

int Checker::get_y()
{
	return this->y;
}

void Checker::set_y(int y)
{
	if(y >= 0 && y < 8)
		this->y = y;
}

void Checker::turn_king()
{
	this->is_king = true;
}

bool Checker::get_is_king()
{
	return this->is_king;
}

TEAM Checker::get_team()
{
	return this->team;
}

void Checker::draw()
{
	int center_x = this->x * SQUARE_SIZE + SQUARE_SIZE / 2;
	int center_y = this->y * SQUARE_SIZE + SQUARE_SIZE / 2;

	DrawCircle(center_x, center_y, 40, this->team == TEAM::R ? RED : BLUE);
}
