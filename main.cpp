#include <iostream>
#include "board.h"
#include "tetris.h"


using namespace std;



int main() {
    board a(2);
    // a.displayGrid();

    tetris test(10);
    std::cout << "Pièce de base" << std::endl;
    test.loadJson("Tetris20");
    std::cout <<"Rotate 90"<< std::endl;
    test.displayPiece(test.getRotatePiece(test.getPieceTetrisEasy("Tetris20")));
    std::cout <<"Flip"<< std::endl;
    test.displayPiece(test.getFlipPiece(test.getPieceTetrisEasy("Tetris20")));
    std::cout <<"place"<< std::endl;
    // a.piecePlace(8,8,test.getPieceTetrisEasy("Tetris20"));
    // a.initializePlayerFirstSquare(2,2,2);
    a.displayGrid();
    test.getListOfPiece();


    return 0;
}
