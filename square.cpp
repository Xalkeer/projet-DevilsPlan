// square.cpp
#include "square.h"

square::square(int val, char turn) : value(val), turn(turn) {}

int square::GetValue() const {
    /*
     * Getter pour la valeur de la case
     **/
    return value ;
}

void square::SetValue(int val) {
    /*
     * Setter pour la valeur de la case
     **/
    value = val ;
}

char square::GetTurn() const {
    /*
     * Getter pour gérer le tour de chaque pièce lors de la pose
     **/
    return turn ;
}

void square::SetTurn(char t) {
    /*
     * Setter pour gérer le tour de chaque pièce lors de la pose
     **/
    turn = t ;
}