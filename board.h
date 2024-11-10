#include <vector>
#include "square.h"
#include "player.h"



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
    void boardColor(std::vector<player> players);

    // void SetValue(int val);
    // void GetValue() const;
};