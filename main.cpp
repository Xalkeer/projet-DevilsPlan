#include <iostream>
#include "board.h"
#include "tetris.h"


using namespace std;



int main() {
    board a(2);
    // a.displayGrid();

    tetris test(10);
    // std::cout << "Pièce de base" << std::endl;
    // test.loadJson("Tetris20");
    // std::cout <<"Rotate 90"<< std::endl;
    // test.displayPiece(test.getRotatePiece(test.getPieceTetrisEasy("Tetris20")));
    // std::cout <<"Flip"<< std::endl;
    // test.displayPiece(test.getFlipPiece(test.getPieceTetrisEasy("Tetris20")));
    std::cout <<"Placement"<< std::endl;
    a.initializePlayerFirstSquare(9,10,5);
    a.initializePlayerFirstSquare(0,0,4);
    a.initializePlayerFirstSquare(0,2,5);
    a.piecePlace(10,10  ,test.getPieceTetrisEasy("Tetris06"), 5);
    a.piecePlace(1,0  ,test.getPieceTetrisEasy("Tetris06"), 4);
    a.piecePlace(3,0  ,test.getPieceTetrisEasy("Tetris06"), 4);
    a.piecePlace(3,2  ,test.getPieceTetrisEasy("Tetris06"), 4);
    a.displayGrid();

    for (int i =0 ; i < test.generateRandomPieceList(1).size(); ++i) {
    test.displayPiece(test.getPieceTetrisEasy(test.generateRandomPieceList(1)[i]));
        std::cout << "bite" << std::endl;
    }
    return 0;
}
