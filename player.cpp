//
// Created by busev on 02/11/2024.
//

#include "player.h"

// Constructeur
player::player(const std::string& name, const std::string& color, int x, int y)
    : name(name), posX(x), posY(y) {}

// Accesseurs
std::string player::getName() const {
    return name;
}


int player::getPosX() const {
    return posX;
}

int player::getPosY() const {
    return posY;
}

// Mutateurs
void player::setName(const std::string& name) {
    this->name = name;
}


void player::setPosition(int x, int y) {
    posX = x;
    posY = y;
}
char player::setcolor() {

}
void player::returncolor(std::vector<std::string> color) {

}

