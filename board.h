#include <vector>
#include "player.h"
#include "square.h"
#include "tetris.h"


class board {
private:
    int nbPlayers;

public:
    std::vector<std::vector<square>> grid;
    board(int nbPlayers);
    void initializeGrid();

    void intializeBonusSquare();

    void initializePlayerFirstSquare(int x, int y, int playerValue);
    int isSquare(int playerValue);
    void displayOtherPiece(std::vector<std::vector<int>> listOfPiece);
    bool piecePlacementVerif(int x, int y, std::vector<std::vector<int>> piece, int playerValue);
    void piecePlace(int x, int y, std::vector<std::vector<int>> piece, int playerValue, int turn);
    int howManyGrass(int playerValue);
    void bonusSquare(std::vector<player> players, int playerValue);
    int bonusVerif(int playerValue);
    void tileExchangeStone(int playerValue, bool isFinish, int x, int y);
    std::vector<std::string> tileExchangeList(std::vector<std::string>& pieceList, int x);
    void Stone(int x, int y);
    void Robbery(int x, int y, int playerValue, int turnCount);
};