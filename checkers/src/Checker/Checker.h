#ifndef CHECKER_H
#define CHECKER_H

class Checker
{
  public:
    Checker(int x, int y);
    void set_x(int x);
    int get_x();

    void set_y(int y);
    int get_y();

    void turn_king();

  private:
    int x;
    int y;
    bool is_king;
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
