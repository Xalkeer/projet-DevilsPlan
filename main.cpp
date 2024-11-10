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

    player b("green",1,1,30,30);

    std::vector<player> players;
    players.push_back(p);
    players.push_back(d);
    players.push_back(b);

    tetris test(10);
    // std::cout << "Pièce de base" << std::endl;
    // test.loadJson("Tetris20");
    // std::cout <<"Rotate 90"<< std::endl;
    // test.displayPiece(test.getRotatePiece(test.getPieceTetrisEasy("Tetris20")));
    // std::cout <<"Flip"<< std::endl;
    // test.displayPiece(test.getFlipPiece(test.getPieceTetrisEasy("Tetris20")));
    //
    // std::cout <<"place"<< std::endl;
    a.piecePlace(0,0,test.getPieceTetrisEasy("Tetris20"));
    a.piecePlace(0,3,test.getPieceTetrisEasy("Tetris19"));
    a.piecePlace(1,3,test.getPieceTetrisEasy("Tetris24"));
    std::cout <<"Board :" << std::endl;
    p.returncolor(p.getColor(), p.setColor() , p.getName() );
    a.boardColor(players);


    return 0;
}