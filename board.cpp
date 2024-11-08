#include "board.h"
#include <iostream>
#include <ostream>
#include "square.h"
#include <vector>
#include "tetris.h"
using namespace std;

board::board(int nbPlayers) : nbPlayers(nbPlayers) {
    initializeGrid();
}
void board::initializeGrid() {
    int gridSize = (nbPlayers > 4) ? 30 : 20;
    grid.resize(gridSize, std::vector<square>(gridSize, square(0)));
    grid[0][0].SetValue(1);
    grid[0][1].SetValue(1);
    grid[1][1].SetValue(1);
    grid[1][0].SetValue(1);
    grid[2][0].SetValue(1);
    grid[2][1].SetValue(1);
    grid[2][2].SetValue(2);
    grid[0][2].SetValue(1);
    grid[1][2].SetValue(1);
}
void board::initializePlayerFirstSquare (int x, int y, int playerValue) {
    grid[x][y].SetValue(playerValue);
}
bool board::isSquare(int playerValue) {
    int maxSize = std::min(grid.size(), grid[0].size());
    for (int size = 2; size <= maxSize; ++size) {
        for (int i = 0; i <= grid.size() - size; ++i) {
            for (int j = 0; j <= grid[i].size() - size; ++j) {
                bool isSquare = true;
                for (int k = 0; k < size; ++k) {
                    for (int l = 0; l < size; ++l) {
                        if (grid[i + k][j + l].GetValue() != playerValue) {
                            isSquare = false;
                            break;
                        }
                    }
                    if (!isSquare) break;
                }
                if (isSquare) return true;
            }
        }
    }
    return false;
}
void board::displayOtherPiece(std::vector<std::vector<int>> listOfPiece) {
    string piece = "Tetris";
    string numberOfPiece = '';
    tetris Tetris(10);
    for (int i = 0; i < listOfPiece.size(); ++i) {
         numberOfPiece = std::to_string(i);
        piece = piece + numberOfPiece ;
        Tetris.getPieceTetrisEasy(piece);
    }
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
            if (x + i < 0 || x + i >= grid.size() || y + j < 0 || y + j >= grid.size()) {
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
            if(board::boardVerif(x,y,piece)) {
                std::cout << "Piece placée : " << std::endl;
                std::cout << piece[0][0] << std::endl;
                grid[x + i][y + j].SetValue(piece[i][j]);
            }
        }
    }
}


