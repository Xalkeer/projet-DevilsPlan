#include <vector>
#include "square.h"


class board {
private:
    int nbPlayers;
    std::vector<std::vector<square>> grid;

public:
    board(int nbPlayers);
    void initializeGrid();
    void initializePlayerFirstSquare(int x, int y, int playerValue);
    bool isSquare(int playerValue);
    void displayOtherPiece(std::vector<std::vector<int>> listOfPiece);
    void displayGrid() const;
    bool boardVerif(int x, int y, std::vector<std::vector<int>> piece);
    void piecePlace(int x, int y,  std::vector<std::vector<int>> piece);
};