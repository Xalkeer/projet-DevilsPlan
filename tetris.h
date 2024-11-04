//
// Created by busev on 02/11/2024.
//

#ifndef TETRIS_H
#define TETRIS_H



class tetris {
private:
   int PlayerValue{};

public :
   tetris(int PlayerValue);

   void testouille();

   void loadJson(std::string nom_piece);
   // void rotatePiece();
   // void FlipPiece();
};



#endif //TETRIS_H
