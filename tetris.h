//
// Created by busev on 02/11/2024.
//

#ifndef TETRIS_H
#define TETRIS_H
#include "json.hpp"


class tetris {
private:
   int PlayerValue{};

public :
   tetris(int PlayerValue);

   void displayPiece(const std::vector<std::vector<int>> &piece);

   std::vector<std::vector<int>> getPieceTetris(const nlohmann::json &pieces, const std::string &nom_piece);

   std::vector<std::vector<int>> getPieceTetrisEasy(const std::string &nom_piece);


   void loadJson(std::string nom_piece);

   std::vector<std::vector<int>> getRotatePiece(const std::vector<std::vector<int>> &piece);

   std::vector<std::vector<int>> getFlipPiece(const std::vector<std::vector<int>> &piece);

   // void rotatePiece();
   // void FlipPiece();
};



#endif //TETRIS_H
