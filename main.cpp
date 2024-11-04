#include <iostream>
#include "board.h"
#include "tetris.h"


using namespace std;



int main() {
    board a(5);
    a.displayGrid();

    tetris test(10);
    std::cout << "Pièce de base" << std::endl;
    test.loadJson("Tetris20");
    std::cout <<"Rotate 90"<< std::endl;
    test.displayPiece(test.getRotatePiece(test.getPieceTetrisEasy("Tetris20")));
    std::cout <<"Flip"<< std::endl;
    test.displayPiece(test.getFlipPiece(test.getPieceTetrisEasy("Tetris20")));

    return 0;
}
