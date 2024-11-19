//
// Created by busev on 02/11/2024.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "display.h"
#include "player.h"
#include "board.h"



class display {
private :
    bool isTakeTileFinish = false;
    std::vector<std::string> pieceList;
public:
    display();
    void initGame();

    bool isAdjacent(int i, int y, const std::vector<std::vector<square>> & grid);
    void initPlacement(std::vector<player> players, int player, board& boardGrid);
    void mainGame(std::vector<player> players, board& gameBoard);
    void exchangedTile(board &gameBoard, player p, std::vector<player> players);
    void tileExchangeList(int x);
    void takeTile(board &gameBoard, player p, std::vector<player> players, int nbPlayer,
                  std::vector<std::vector<int>> piece, int turnCount);
    void putTile(board& gameBoard, player p, int nbPlayer, std::vector<std::vector<int>> piece, int turnCount);
    void boardColor(std::vector<player> players, const board &gameBoard);

};



#endif //DISPLAY_H
