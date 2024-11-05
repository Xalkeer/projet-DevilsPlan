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
            std::cout << grid[i][j].GetValue() << " ";
        }
        std::cout << std::endl;
    }
}
bool board::boardVerif(int x, int y, std::vector<std::vector<int>> piece) {
    for (int i = 0; i < piece.size(); ++i) {
        for (int j = 0; j < piece[i].size(); ++j) {
            // Vérifie les limites du Board
            if (x + i > 0 || x + i < grid.size() || y + j > 0 || y + j < grid[0].size()) {
                return false; // Sortie des limites du Board
            }
            // Vérifie si la case est libre sur le Board
            if (piece[i][j] != 0 && grid[x + i][y + j].GetValue() != 0) {
                return false; // Position déjà occupée
            }
        }
    }
    return true; // Placement possible
}

void board::piecePlace(int x, int y, std::vector<std::vector<int>> piece) {

    for (int i =0; i <  piece.size(); ++i) {
        for (int j = 0; j <  piece[i].size(); ++j) {
            std::cout << "Tours : " << i << " " << j << std::endl;
            std::cout<< "Piece : " << piece[i][j] << std::endl;
            //if(board::boardVerif(x,y,piece)) {
                std::cout << "Piece placée : " << std::endl;
                std::cout << piece[0][0] << std::endl;
                grid[x + i][y + j].SetValue(piece[i][j]);
                displayGrid();
            //}
        }
    }
}


