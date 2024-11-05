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

    bool boardVerif(int x, int y, std::vector<std::vector<int>> piece);

    void piecePlace(int x, int y,  std::vector<std::vector<int>> piece);

    // void SetValue(int val);
    // void GetValue() const;
};