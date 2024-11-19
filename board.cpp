#include <vector>
#include <iostream>
#include <ostream>
#include "board.h"

#include <random>

using namespace std;

board::board(int nbPlayers) : nbPlayers(nbPlayers) {
    /*
     * initialisation du board et des case bonus
     **/
    initializeGrid();
    intializeBonusSquare();
}
void board::initializeGrid() {
    /*
     * initialisation du board 20x20 entre 2 et 4 joueur et 30x30 pour 5 et 9 joueur
     **/
    int gridSize = (nbPlayers > 4) ? 30 : 20;
    grid.resize(gridSize, std::vector<square>(gridSize, square(0, 'P')));
}
void board::intializeBonusSquare() {
    /*
     * initialisation des cases bonus pour chaque joueur
     * 1.5 fois le nombre de joueur pour la case de changement de tuile
     * 0.5 fois le nombre de joueur pour la case de pierre
     * 1 fois le nombre de joueur pour la case de vole
     **/
    int nbCaseTileExchange = nbPlayers * 1.5;
    int nbCaseStone = static_cast<int>(nbPlayers * 0.5);
    int nbCaseRoberry = nbPlayers;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, grid.size() - 1);

    for (int i = 0; i < nbCaseTileExchange; ++i) {
        int x = dis(gen);
        int y = dis(gen);
        if (grid[x][y].GetValue() == 0) {
            grid[x][y].SetValue(10);
        }
    }
    for (int i = 0; i < nbCaseStone; ++i) {
        int x = dis(gen);
        int y = dis(gen);
        if (grid[x][y].GetValue() == 0) {
            grid[x][y].SetValue(11);
        }
    }
    for (int i = 0; i < nbCaseRoberry; ++i) {
        int x = dis(gen);
        int y = dis(gen);
        if (grid[x][y].GetValue() == 0) {
            grid[x][y].SetValue(12);
        }
    }
}
void board::initializePlayerFirstSquare (int x, int y, int playerValue) {
    /*
    * Mise en place de la 1ere case 1x1 du joueur au debut de jeux
    **/
    grid[x][y].SetValue(playerValue);
    grid[x][y].SetTurn('0' + playerValue);
}
int board::isSquare(int playerValue) {
    /*
    * verification de fin de jeu
    * verifie la taille du territoire du joueur
    **/
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
bool board::piecePlacementVerif(int x, int y, std::vector<std::vector<int>> piece, int playerValue) {
    /*
    * Vérifie si la pièce peut être placée sur le Board
    * Vérifie les limites du Board, si la case est libre, si la pièce touche bien une case du joueur de base,
    * et si la pièce ne touche pas une case d'un autre joueur
    * sinon renvoie un message d'erreur selon la verification
    **/
    bool playerSquareAround = false;
    for (int i = 0; i < piece.size(); ++i) {
        for (int j = 0; j < piece[i].size(); ++j) {
            // Vérifie les limites du Board
            if (x + i < 0 || x + i >= grid.size() || y + j < 0 || y + j >= grid[0].size()) {
                std::cout << "Sortie des limites du Board" << std::endl;
                return false;
            }
            // Vérifie si la case est libre sur le Board
            int cellValue = grid[x + i][y + j].GetValue();
            if (piece[i][j] != 0 && cellValue != 0 && (cellValue < 10 || cellValue > 15)) {
                std::cout << "Position déjà occupee" << std::endl;
                return false;
            }

            // Vérifie si la pièce placée touche bien une case du joueur de base
            if (piece[i][j] != 0) {
                if ((x + i > 0 && grid[x + i - 1][y + j].GetValue() == playerValue) || // Check haut
                    (x + i < grid.size() - 1 && grid[x + i + 1][y + j].GetValue() == playerValue) || // Check bas
                    (y + j > 0 && grid[x + i][y + j - 1].GetValue() == playerValue) || // Check gauche
                    (y + j < grid[0].size() - 1 && grid[x + i][y + j + 1].GetValue() == playerValue)) { // Check droite
                    playerSquareAround = true;
                }
                if ((x + i > 0 && grid[x + i - 1][y + j].GetValue() != 0 && grid[x + i - 1][y + j].GetValue() != playerValue && (grid[x + i - 1][y + j].GetValue() < 10 || grid[x + i - 1][y + j].GetValue() > 15)) || // Check haut
                    (x + i < grid.size() - 1 && grid[x + i + 1][y + j].GetValue() != 0 && grid[x + i + 1][y + j].GetValue() != playerValue && (grid[x + i + 1][y + j].GetValue() < 10 || grid[x + i + 1][y + j].GetValue() > 15)) || // Check bas
                    (y + j > 0 && grid[x + i][y + j - 1].GetValue() != 0 && grid[x + i][y + j - 1].GetValue() != playerValue && (grid[x + i][y + j - 1].GetValue() < 10 || grid[x + i][y + j - 1].GetValue() > 15)) || // Check gauche
                    (y + j < grid[0].size() - 1 && grid[x + i][y + j + 1].GetValue() != 0 && grid[x + i][y + j + 1].GetValue() != playerValue && (grid[x + i][y + j + 1].GetValue() < 10 || grid[x + i][y + j + 1].GetValue() > 15))) { // Check droite
                    std::cout << "La piece touche une case d'un autre joueur" << std::endl;
                    return false;
    }
            }
        }
    }
    if (!playerSquareAround) {
        std::cout << "La pièce doit toucher au moins une case du joueur" << std::endl;
        return false;
    }
    return true; // Placement possible
}
void board::piecePlace(int x, int y, std::vector<std::vector<int>> piece, int playerValue, int turnCount) {
    /*
    * Place la pièce sur le Board
    * Met à jour les cases occupées par la pièce et change les valeurs des cases de la pièce
    **/
    for (int i =0; i <  piece.size(); ++i) {
        for (int j = 0; j <  piece[i].size(); ++j) {
            if (piece[i][j] != 0) {
                grid[x + i][y + j].SetValue(playerValue);
                if (turnCount == 0) {
                    grid[x + i][y + j].SetTurn('A' );
                }
                else {
                    grid[x + i][y + j].SetTurn('A' +(turnCount));
                }
            }
        }
    }
}
int board::howManyGrass(int playerValue) {
    /*
    * Affiche le nombre de cases de la pièce du joueur
    **/
    int count = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j].GetValue() == playerValue) {
                count++;
            }
        }
    }
    return count ;
}
void board::bonusSquare(std::vector<player> players, int playerValue){
    /*
    * Vérifie si le joueur entoure bien une case bonus et exécute les actions correspondantes au bonus
    **/
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[i].size(); ++j){
            if (bonusVerif(playerValue) == true){
                int x;
                int y;
                switch (grid[i][j].GetValue()) {
                    case 10:
                        players[grid[i-1][j].GetValue()-1].addTileExchange();
                    case 11:
                        std::cout << "x" << std::endl;
                    cin >> x;
                    std::cout << "y" << std::endl;
                    cin >> y;
                    Stone(x, y);
                    case 12:
                        std::cout << "x" << std::endl;
                    cin >> x;
                    std::cout << "y" << std::endl;
                    cin >> y;
                    Robbery(x,y,playerValue,10);
                }
            }
        }
    }
}
int board::bonusVerif(int playerValue){
    /*
    * Vérifie si le joueur entoure bien une case bonus
    **/
    int result = 0 ;
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[i].size(); ++j){
            if (grid[i][j].GetValue() >= 10 && grid[i][j].GetValue() < 15){
                if (grid[i+1][j].GetValue() == playerValue
                    && grid[i-1][j].GetValue() == playerValue
                    && grid[i][j+1].GetValue() == playerValue
                    && grid[i][j-1].GetValue() == playerValue ){
                    result = grid[i][j].GetValue();
                    return result;
                }else{
                    return result;
                }
            }else {return result;}
        }
    }
    return result;
}
// MODIFIER LE TURN
void board::tileExchangeStone(int playerValue, bool isFinish, int x, int y){
    /*
     * verifie en cours de jeu si la piece choisit est bien une pierre et la remplace par une case joueur
     * place une case 1x1 cas de fin de jeu
     **/
    cout << grid[x][y].GetValue() << endl;
    if (isFinish == false && grid[x][y].GetValue() == 15 ){
        grid[x][y].SetValue(playerValue);
    }else if(isFinish == true && grid[x][y].GetValue() == 0){
        grid[x][y].SetValue(playerValue);
    }
}

void board::Stone (int x, int y){
    /*
     *place une pierre dans une case vide du board
     **/
    if(grid[x][y].GetValue() == 0 ){
        grid[x][y].SetValue(15);
    }
}
void board::Robbery(int x, int y, int playerValue, int turnCount) {
    /*
     *recupere une piece d'un joueur pour le mettre dans son territoire
     **/
    char turn = grid[x][y].GetTurn();
    std::vector<std::vector<int>> pieceCoordinates;
    // Find all coordinates of the piece
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j].GetTurn() == turn && grid[i][j].GetValue() != playerValue) {
                pieceCoordinates.push_back({i, j});
                grid[i][j].SetValue(0);
                grid[i][j].SetTurn('P');
            }
        }
    }
    // Convert coordinates to piece format
    int minX = grid.size(), minY = grid[0].size();
    for (const auto& coord : pieceCoordinates) {
        if (coord[0] < minX) minX = coord[0];
        if (coord[1] < minY) minY = coord[1];
    }

    std::vector<std::vector<int>> piece;
    for (const auto& coord : pieceCoordinates) {
        int newX = coord[0] - minX;
        int newY = coord[1] - minY;
        if (piece.size() <= newX) piece.resize(newX + 1);
        if (piece[newX].size() <= newY) piece[newX].resize(newY + 1);
        piece[newX][newY] = 1;
    }
    // Allow the current player to place the piece in their game
    int newPlaceX, newPlaceY;
    tetris Tetris;
    Tetris.displayPiece(piece);
    do {
        std::cout << "Enter the new coordinates to place the stolen piece:" << std::endl;
        cout << "Line (most top-left square of the tile)" << endl;
        cout << "Column (most top-left square of the tile)" << endl;
        std::cin >> newPlaceX >> newPlaceY;
        newPlaceX -= 1;
        newPlaceY -= 1;
    } while (!piecePlacementVerif(newPlaceX, newPlaceY, piece, playerValue));
    piecePlace(newPlaceX, newPlaceY, piece, playerValue, turnCount);
}