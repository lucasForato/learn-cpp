#include "Checker.h"

Checker::Checker(int x, int y)
	: x{x}
	, y{y}
	, is_king{false}
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
