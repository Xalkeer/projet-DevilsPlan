#include <iostream>
#include "board.h"
#include "player.h"
#include "tetris.h"


using namespace std;



int main() {
    board a(2);
    // a.displayGrid();
    player p("red",0,1,10,10);

    player d("blue",2,1,20,20);

    tetris test(10);
    std::cout << "Pièce de base" << std::endl;
    test.loadJson("Tetris20");
    std::cout <<"Rotate 90"<< std::endl;
    test.displayPiece(test.getRotatePiece(test.getPieceTetrisEasy("Tetris20")));
    std::cout <<"Flip"<< std::endl;
    test.displayPiece(test.getFlipPiece(test.getPieceTetrisEasy("Tetris20")));

    std::cout <<"place"<< std::endl;
    a.piecePlace(0,0,test.getPieceTetrisEasy("Tetris20"));
    std::cout <<"Board :"<< std::endl << std::endl;
    a.displayGrid();
    std::vector<std::pair<int, std::string>> color ;
    color = p.setColor();
    int c = p.getColor();
    p.returncolor(c,color , "test" );
    a.boardColor(p);


    return 0;
}
