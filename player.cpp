//
// Created by busev on 02/11/2024.
//

#include "player.h"

// Constructeur
player::player(const std::string& name, const std::string& color, int x, int y)
    : name(name), color(color), posX(x), posY(y) {}

// Accesseurs
std::string player::getName() const {
    return name;
}

std::string player::getColor() const {
    return color;
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

void player::setColor(const std::string& color) {
    this->color = color;
}

void player::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

