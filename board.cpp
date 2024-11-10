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

}
void board::initializePlayerFirstSquare (int x, int y, int playerValue) {
    grid[x][y].SetValue(playerValue);
}
int board::isSquare(int playerValue) {
    int maxSize = std::min(grid.size(), grid[0].size());
    int largestSquareSize = 0;
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
                if (isSquare) {
                    largestSquareSize = size;
                }
            }
        }
    }
    return largestSquareSize;
}
void board::displayOtherPiece(std::vector<std::vector<int>> listOfPiece) {
    string piece = "Tetris";
    // string numberOfPiece = '';
    // tetris Tetris(10);
    // for (int i = 0; i < listOfPiece.size(); ++i) {
    //      numberOfPiece = std::to_string(i);
    //     piece = piece + numberOfPiece ;
    //     Tetris.getPieceTetrisEasy(piece);
    // }
}
void board::displayGrid() const {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j].GetValue() << " ";
        }
        std::cout << std::endl;
    }
}
bool board::piecePlacementVerif(int x, int y, std::vector<std::vector<int>> piece, int playerValue) {
    bool playerSquareAround = false;
    for (int i = 0; i < piece.size(); ++i) {
        for (int j = 0; j < piece[i].size(); ++j) {
            // Vérifie les limites du Board
            if (x + i < 0 || x + i >= grid.size() || y + j < 0 || y + j >= grid.size()) {
                std::cout << "Sortie des limites du Board" << std::endl;
                return false;
            }
            // Vérifie si la case est libre sur le Board
            if (piece[i][j] != 0 && grid[x + i][y + j].GetValue() != 0 ) {
                std::cout << "Position déjà occupée" << std::endl;
                return false;
            }
            //Vérifie, si la pièce placé touche bien une case du joueur de base
            if (piece[i][j] != 0) {
                if ((x + i > 0 && grid[x + i - 1][y + j].GetValue() == playerValue) || // Check haut
                    (x + i < grid.size() - 1 && grid[x + i + 1][y + j].GetValue() == playerValue) || // Check bas
                    (y + j > 0 && grid[x + i][y + j - 1].GetValue() == playerValue) || // Check gauche
                    (y + j < grid[0].size() - 1 && grid[x + i][y + j + 1].GetValue() == playerValue)) { // Check droite
                    playerSquareAround = true;
                    }
                if ((x + i > 0 && grid[x + i - 1][y + j].GetValue() != 0 && grid[x + i - 1][y + j].GetValue() != playerValue) || // Check haut
                    (x + i < grid.size() - 1 && grid[x + i + 1][y + j].GetValue() != 0 && grid[x + i + 1][y + j].GetValue() != playerValue) || // Check bas
                    (y + j > 0 && grid[x + i][y + j - 1].GetValue() != 0 && grid[x + i][y + j - 1].GetValue() != playerValue) || // Check gauche
                    (y + j < grid[0].size() - 1 && grid[x + i][y + j + 1].GetValue() != 0 && grid[x + i][y + j + 1].GetValue() != playerValue)) { // Check droite
                    std::cout << "La pièce touche une case d'un autre joueur" << std::endl;
                    return false;
                    }
            }
            if (!playerSquareAround) {
                std::cout << "La pièce doit toucher au moins une case du joueur" << std::endl;
                return false;
            }
        }
    }
    return true; // Placement possible
}
void board::piecePlace(int x, int y, std::vector<std::vector<int>> piece, int playerValue) {
    if(board::piecePlacementVerif(x,y,piece,playerValue)) {
        for (int i =0; i <  piece.size(); ++i) {
            for (int j = 0; j <  piece[i].size(); ++j) {
                if (piece[i][j] != 0) {
                    grid[x + i][y + j].SetValue(playerValue);
                }
            }
        }
    }
}
void board::howManyGrass(int playerValue) {
    int count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j].GetValue() == playerValue) {
                count++;
            }
        }
    }
    std::cout << "Le joueur " << playerValue << " a " << count << " cases" << std::endl;
}
