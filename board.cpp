#include "board.h"
#include <iostream>
#include <ostream>
#include "square.h"
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
            if (0 < x + i  || x + i < grid.size() || 0 < y + j  || y + j < grid[0].size()) {
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
            //if(board::boardVerif(x,y,piece)) {
                grid[x + i][y + j].SetValue(piece[i][j]);
            //}else{
            //    std::cout << "pas possible" << std::endl;
            //}
        }
    }
}
void board::boardColor(std::vector<player> players){
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[i].size(); ++j){
            std::vector<std::pair<int, std::string>> colors = players[grid[i][j].GetValue()].setColor() ;
            if (players[grid[i][j].GetValue()].getColor() >= 0 && players[grid[i][j].GetValue()].getColor() < static_cast<int>(colors.size())){
                if (grid[i][j].GetValue() >= 1 )
                {
                    std::cout << colors[players[grid[i][j].GetValue()-1].getColor()].second << grid[i][j].GetValue() << colors[players[grid[i][j].GetValue()-1].getColor()].second << " ";
                } else {
                    std::cout << "\e[0m" << grid[i][j].GetValue() << "\e[0m" << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}




