#include <iostream>
#include "Board.h"

using namespace std;

Board::Board()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++) board[i][j] = ' ';
  }
}

void Board::render()
{
  cout << "  " << "A" << "   " << "B" << "   " << "C" << '\n';
  for (int i = 0; i < 3; i++)
  {
    cout << (i + 1) << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << '\n';
    if (i != 2) cout << " -----------" << '\n';
  }
  cout << '\n';
}

void Board::set_element(int x, int y, Tile tile)
{
  board[x][y] = tile == Tile::X ? 'X' : 'O';
}

Tile Board::check_winner()
{
  for (int i = 0; i < 3; i++)
  {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
    {
      if (board[i][0] == 'X') return Tile::X;
      if (board[i][0] == 'O') return Tile::O;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
    {
      if (board[0][i] == 'X') return Tile::X;
      if (board[0][i] == 'O') return Tile::O;
    }
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
  {
    if (board[0][0] == 'X') return Tile::X;
    if (board[0][0] == 'O') return Tile::O;
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
  {
    if (board[0][2] == 'X') return Tile::X;
    if (board[0][2] == 'O') return Tile::O;
  }
  return Tile::None;
}
