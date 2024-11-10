#include <iostream>
#include "board.h"
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
    std::cout <<"Placement"<< std::endl;
    a.initializePlayerFirstSquare(9,10,2);
    a.initializePlayerFirstSquare(0,0,1);
    a.initializePlayerFirstSquare(0,2,2);
    a.initializePlayerFirstSquare(10,15,3);
    a.piecePlace(10,10  ,test.getPieceTetrisEasy("Tetris06"), 2);
    a.piecePlace(1,0  ,test.getPieceTetrisEasy("Tetris06"), 1);
    a.piecePlace(3,0  ,test.getPieceTetrisEasy("Tetris06"), 1);
    a.piecePlace(3,2  ,test.getPieceTetrisEasy("Tetris06"), 1);

    // for (int i =0 ; i < test.generateRandomPieceList(1).size(); ++i) {
    // test.displayPiece(test.getPieceTetrisEasy(test.generateRandomPieceList(1)[i]));
    //     std::cout << "bite" << std::endl;
    // }
    a.displayGrid();
    p.returncolor(p.getColor(), p.setColor() , p.getName() );
    a.boardColor(players);
    return 0;
}
