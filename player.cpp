//
// Created by busev on 02/11/2024.
//
#include <iostream>
#include "player.h"

player::player(const std::string& name, int color, int tileExchange, int x, int y)
    : name(name), color(color), tileExchange(tileExchange), posX(x), posY(y) {}

std::string player::getName() const {
    return name;
}
int player::getColor() const
{
    return color;
}
int player::getPosX() const {
    return posX;
}

int player::getPosY() const {
    return posY;
}
int player::getTileExchange() const
{
    return tileExchange;
}

void player::setName(const std::string& name) {
    this->name = name;
}

void player::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void player::addTileExchange() {
    ++tileExchange;
}
bool player::useTileExchange() {
    if (tileExchange > 0) {
        --tileExchange;
        return true;
    }
    return false;
}


std::vector<std::pair<int, std::string>> player::setColor() {
    std::vector<std::pair<int, std::string>> color = {
        //1 Rouge , 2Vert ,3 Bleu,4 Noir,5 Blanc,6 Jaune,7 Cyan,8 Magenta
        {1, "\e[0;31m"},
        {2, "\e[0;32m"},
        {3, "\e[0;34m"},
        {4, "\e[0;30m"},
        {5, "\e[0;37m"},
        {6, "\e[0;33m"},
        {7, "\e[0;36m"},
        {8, "\e[0;35m"}
    };
    return color;
}
void player::returncolor(int indexCouleur, const std::vector<std::pair<int, std::string>>& colors, const std::string& texte) {
    if (indexCouleur >= 0 && indexCouleur < static_cast<int>(colors.size())) {
        std::cout << colors[indexCouleur].second << texte << colors[indexCouleur].second << std::endl;
    } else {
        std::cout << "Index de couleur invalide. Texte sans couleur : " << texte << std::endl;
    }
}


