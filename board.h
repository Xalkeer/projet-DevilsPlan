#include <vector>

#include "player.h"
#include "square.h"


class board {
private:
    int nbPlayers;
    std::vector<std::vector<square>> grid;

public:
    board(int nbPlayers);
    void initializeGrid();
    void initializePlayerFirstSquare(int x, int y, int playerValue);
    int isSquare(int playerValue);
    void displayOtherPiece(std::vector<std::vector<int>> listOfPiece);
    void displayGrid() const;
    bool piecePlacementVerif(int x, int y, std::vector<std::vector<int>> piece, int playerValue);
    void piecePlace(int x, int y,  std::vector<std::vector<int>> piece, int playerValue);

    void howManyGrass(int playerValue);

    void boardColor(std::vector<player> players);
};