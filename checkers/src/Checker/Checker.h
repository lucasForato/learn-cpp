#ifndef CHECKER_H
#	define CHECKER_H

enum TEAM
{
	R,
	B
};

class Checker
{
public:
	Checker(int x, int y, TEAM team);
	void set_x(int x);
	int get_x();

	void set_y(int y);
	int get_y();

	void turn_king();

	TEAM get_team();

  bool get_is_king();

  void draw();

private:
	int x;
	int y;
	bool is_king;
	TEAM team;
};

#endif

/*

  Checkers[] -> for team A
  Checkers[] -> for team B
  
  A checker has:
  - x_position
  - y_position
  - is_king

*/
