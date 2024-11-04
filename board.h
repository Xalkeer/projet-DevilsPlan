#include <vector>
#include "square.h"


class board {
private:
    int nbPlayers;
    std::vector<std::vector<square>> grid;

public:
    board(int nbPlayers);
    void initializeGrid();
    void displayGrid() const;
    void Pieceplace(int x, int y);
};