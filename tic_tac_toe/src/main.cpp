#include <iostream>
#include "Board.h"
#include <string>

using namespace std;

int main() 
{
  cout << "Welcome to Tic Tac Toe." << '\n';
  Board board;

  Tile tile = Tile::X;
  while (board.check_winner() == Tile::None) {
    string coords;

    board.render();

    cout << "Enter coordinates, e.g. A1, C2 > ";
    cin >> coords;
    cout << '\n';

    int y = coords[0] - 'A';
    int x = coords[1] - '1';

    board.set_element(x, y, tile);
    tile = tile == Tile::X ? Tile::O : Tile::X;
  }

  char winner = board.check_winner() == Tile::X ? 'X' : 'O';
  cout << "The winner is: " << winner << '\n';
  
  return 0;
}
