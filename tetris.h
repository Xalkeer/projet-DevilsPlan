//
// Created by busev on 02/11/2024.
//

#ifndef TETRIS_H
#define TETRIS_H
#include "json.hpp"


class tetris {
public :
   tetris();

   void displayPiece(const std::vector<std::vector<int>> &piece);
   std::vector<std::vector<int>> getPieceTetris(const nlohmann::json &pieces, const std::string &nom_piece);
   std::vector<std::vector<int>> getPieceTetrisEasy(const std::string &nom_piece);
   std::vector<std::vector<int>> getRotatePiece(const std::vector<std::vector<int>> &piece);
   std::vector<std::vector<int>> getFlipPiece(const std::vector<std::vector<int>> &piece);

   std::vector<std::string> generateRandomPieceList(int numberOfPlayers);
};



#endif //TETRIS_H
