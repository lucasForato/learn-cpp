
#ifndef BOARD_H
#define BOARD_H

enum class Tile { X, O, None };

class Board
{
  public:
    Board();
    void render();
    Tile check_winner();

    char get_element(int x, int y);
    void set_element(int x, int y, Tile player);

  private:
        char board[3][3];
};

#endif
