//
// Created by busev on 02/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <string>



class player {
private:
    std::string name;
    std::string color;
    int posX = 0;
    int posY = 0;



public:
    // Constructeur
    player(const std::string& name, const std::string& color, int x, int y);

    // Accesseurs
    std::string getName() const;
    int getPosX() const;
    int getPosY() const;

    // Mutateurs
    void setName(const std::string& name);
    void setPosition(int x, int y);

    char setcolor();
    void returncolor(std::vector<std::string> color);
};



#endif //PLAYER_H
