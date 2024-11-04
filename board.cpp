#include "board.h"
#include <iostream>
#include <ostream>
#include "square.h"
#include <vector>
#include "tetris.h"


board::board(int nbPlayers) : nbPlayers(nbPlayers) {
    initializeGrid();
}

void board::initializeGrid() {
    int gridSize = (nbPlayers > 4) ? 30 : 20;
    grid.resize(gridSize, std::vector<square>(gridSize, square(0)));
}
void board::displayGrid() const {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j].getValue() << " ";
        }
        std::cout << std::endl;
    }
}
void board::Pieceplace(int x, int y) {
    std::vector<std::vector<int>> piece ;
    tetris test(10);
    test.loadJson("Tetris03") ;
    piece = test.getPieceTetris(const nlohmann::json &pieces, const std::string &nom_piece)



}
