//
// Created by busev on 02/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>



class player
{
private:
    std::string name;
    int color;
    int tileExchange = 1 ;
    int posX = 0;
    int posY = 0;




public:
    player(const std::string& name, int color, int tileExchange, int x, int y);

    std::string getName() const;
    int getColor() const;
    int getPosX() const;
    int getPosY() const;
    int getTileExchange() const;

    void setName(const std::string& name);
    void setColor(int color);
    void setPosition(int x, int y);

    void addTileExchange() ;
    bool useTileExchange() ;

    std::vector<std::pair<int, std::string>> setColor();
    void returncolor(int indexCouleur, const std::vector<std::pair<int, std::string>>& colors, const std::string& texte) ;
};



#endif //PLAYER_H