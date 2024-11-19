//
// Created by busev on 02/11/2024.
//
#include <iostream>
#include "player.h"

player::player(const std::string& name, int color, int tileExchange, int x, int y, int playerValue, int turnCount )
    : name(name), color(color), tileExchange(tileExchange), posX(x), posY(y), playerValue(playerValue), turnCount(turnCount)  {}

int player::getPlayerValue() const {
    /*
     * Getter pour la valeur du joueur
     **/
    return playerValue;
}

int player::getTurnCount() const {
    std::cout << turnCount << std::endl;
    return turnCount;
}

void player::setTurn()  {
    ++turnCount;
}
std::string player::getName() const {
    /*
     * Getter du nom du joueur (caractère)
     **/
    return name;
}
int player::getColor() const{
    /*
    * Getter pour la valeur de la couleur
    **/
    return color;
}
int player::getPosX() const {
    /*
     * Getter pour la horizontale du la case de depart 1x1
     **/
    return posX;
}

int player::getPosY() const {
    /*
     * Getter pour la verticale du la case de depart 1x1
     **/
    return posY;
}
int player::getTileExchange() const{
    /*
     * Getter pour la valeur de coupon d'echanges du joueur
     **/
    return tileExchange;
}

void player::setName(const std::string& name) {
    /*
     * Setter du nom du joueur (caractère)
     **/
    this->name = name;
}

void player::setPosition(int x, int y) {
    /*
     * Setter pour la position de depart utilisant les coordonnes donne par le joueur
     **/
    posX = x;
    posY = y;
}

void player::addTileExchange() {
    /*
     * Incrementer le nombre de coup d'echanges du joueur
     **/
    ++tileExchange;
}
void player::useTileExchange() {
    /*
     * Decrementer le nombre de coup d'echanges du joueur
     **/
    if (tileExchange > 0) {
        --tileExchange;
    }
}


std::vector<std::pair<int, std::string>> player::setColor() {
    std::vector<std::pair<int, std::string>> color = {
        /*
         *mise en place d'une liste de couleur pour l'affichage
         **/
        // 0, reset ,1 Vert , 2 Bleu ,3 Bleu,4 Gris ,5 Blanc,6 Jaune,7 Cyan,8 Magenta,9 Noir, 10 Blanc clair
        {0, "\e[0m" },
        {1, "\e[0;31m"},
        {2, "\e[0;33m"},
        {3, "\e[0;34m"},
        {4, "\e[0;30m"},
        {5, "\e[0;37m"},
        {6, "\e[0;33m"},
        {7, "\e[0;36m"},
        {8, "\e[0;35m"},
        {9, "\e[0;90m"},
        {10, "\e[0;97m"},
    };
    return color;
}
void player::returncolor(int indexCouleur, const std::vector<std::pair<int, std::string>>& colors, const std::string& texte) {
    /*
     * Affichage de la couleur du joueur pour un texte donne
     **/
    if (indexCouleur >= 0 && indexCouleur < static_cast<int>(colors.size())) {
        std::cout << colors[indexCouleur].second << texte << colors[indexCouleur].second << std::endl;
    } else {
        std::cout << "Index de couleur invalide. Texte sans couleur : " << texte << std::endl;
    }
}