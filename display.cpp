#include <iostream>
#include <thread>
#include <chrono>
#include "display.h"

using namespace std;

display::display() {}
void display::initGame() {
    /*
     * - Affichage du message de bienvenue
     * - demande le nombre de joueur de 2 a 9
     * - creez le joueur avec son nom et la valeur de sa couleur
     * - affichage du board avec les case bonus
     * - demande le carre de depart du joueur
     **/
    int nbPlayers;
    cout << " ---------------------------------" << endl;
    cout << "Welcome to the Laying Grass" << endl;
    cout << "Please, choose the number of players (2 to 9) : "<< endl;
    cout << " ---------------------------------" << endl;
    while (true) {
        cin >> nbPlayers;
        if (cin.fail() || nbPlayers > 9 || nbPlayers < 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, choose a number between 2 and 9." << endl;
        } else {
            break;
        }
    }
    cout << "You have chosen " << nbPlayers << " players." << endl;
    board gameBoard(nbPlayers);
    vector<player> players;
    for (int i = 0; i < nbPlayers; ++i) {
        string name;
        int color;
        bool validName = false;
        bool validColor = false;
        while (!validName) {
            cout << "Player " << i + 1 << " : " << endl;
            cout << "Please, choose your name : ";
            cin >> name;
            validName = true;
            for (const auto& p : players) {
                if (p.getName() == name) {
                    cout << "This name is already taken. Please choose a different name." << endl;
                    validName = false;
                    break;
                }
            }
        }
        while (!validColor) {
            cout << "Please, choose your color (1 to 8) : ";
            cin >> color;
            validColor = true;
            for (const auto& p : players) {
                if (p.getColor() == color) {
                    cout << "This color is already taken. Please choose a different color." << endl;
                    validColor = false;
                    break;
                }
            }
        }
        players.emplace_back(name, color, 1, 0, 0,i + 1,0);
        cout << "Player " << i + 1 << " is ready." << endl;
    }
    initPlacement(players, nbPlayers, gameBoard);
    tetris Tetris;
    pieceList = Tetris.generateRandomPieceList(players.size());
    cout << "The game is ready to start." << endl;
    mainGame(players,gameBoard);
}
bool display::isAdjacent(int x, int y, const vector<vector<square>>& grid) {
    /*
     * verifie si la case de depart choisit par le joueur est colle a une case deja occuper
     **/
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 && j == 0)) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
                if (grid[newX][newY].GetValue() != 0 || grid[newX][newY].GetValue() >= 10) {
                    return true;
                }
            }
        }
    }
    return false;
}
void display::initPlacement(vector<player> players, int player, board& gameBoard) {
    /*
     * demande les coordonnes x et y du joueur pour placer la case de depart de la partie
     * verifie si la case de depart est colle a une case deja occuper
     * affiche le board avec les case bonus
     **/
    for (int i = 0; i < players.size(); ++i) {
        int x, y;
        bool validPosition = false;
        boardColor(players, gameBoard);
        while (!validPosition) {
            cout << players[i].getName() << " : " << endl;
            cout << "Please, choose your position (x y) : ";
            cin >> x >> y;
            x -= 1;
            y -= 1;
            if (isAdjacent(x, y, gameBoard.grid) || gameBoard.grid[x][y].GetValue() != 0 || x < 0 || x >= gameBoard.grid.size() || y < 0 || y >= gameBoard.grid[0].size()) {
                cout << "Position is invalid. Please choose a different position." << endl;
            } else {
                validPosition = true;
            }
        }
        players[i].setPosition(x, y);
        cout << "You have chosen the position (" << players[i].getPosX() << ", " << players[i].getPosY() << ")." << endl;
        gameBoard.initializePlayerFirstSquare(x, y, i + 1);
    }
}
void display::mainGame(vector<player> players, board& gameBoard) {
    cout << " ---------------------------------" << endl;
    int turn = 0;
    tetris Tetris;
    for (int i = 0; i < 9 ; i++ ) {
        for (auto& p : players) {
            cout << " ---------------------------------" << endl;
            cout << "Next tiles : " << endl;
            for (int i = 1; i < 6; ++i) {
                Tetris.displayPiece(Tetris.getPieceTetrisEasy(pieceList[i]));
                cout << " "<<endl;
                cout << " ---------------------------------" << endl;
            }
            boardColor(players,gameBoard);
            cout << "Player : "<<p.getName() << endl;
            cout << "Current tile : " << endl;
            Tetris.displayPiece(Tetris.getPieceTetrisEasy(pieceList[0]));
            cout << " ---------------------------------" << endl;
            cout << "Take Tile (1)" << endl;
            cout << "Exchange tile - "<< p.getTileExchange() << " available (2)" << endl;
            cout << " ---------------------------------" << endl;
            int playerChoice;
            cin >> playerChoice;
            // 1 = take tile
            // 2 = exchange tile
            if (playerChoice == 1) {
                cout << "You have taken a tile." << endl;
                takeTile(gameBoard, p,players, players.size(), Tetris.getPieceTetrisEasy(pieceList[0]) ,i);
                if (isTakeTileFinish == true) {
                    turn += 1;
                    pieceList.erase(pieceList.begin());
                    if (gameBoard.bonusVerif(p.getPlayerValue())) {
                        cout <<" You found a Exchange ticket" << endl;
                        p.addTileExchange();
                        cout <<" You got now " << p.getTileExchange() << " tile exchange" << endl;
                        this_thread::sleep_for(chrono::seconds(3));
                    }else if (gameBoard.bonusVerif(p.getPlayerValue())){
                        cout <<" You can now transform a grass block into a stone" << endl;
                        int x,y ;
                        cout << "Where do you want to place a stone" << endl;
                        cin >> x >> y;
                        x -= 1;
                        y -= 1;
                        gameBoard.Stone(x,y);
                    }
                    else if (gameBoard.bonusVerif(p.getPlayerValue())) {
                        cout <<"You can now steal a tile from yours opponents" << endl;
                        int x ,y ;
                        cout << "Where do you want to steal a tile from your opponent" << endl;
                        cin >> x >> y;
                        x -= 1;
                        y -= 1;
                        p.setTurn();
                        gameBoard.Robbery(x,y,p.getPlayerValue(),i);
                    }
                }
            }
            else if (playerChoice == 2) {
                exchangedTile(gameBoard, p,players);
            }
            else {
                cout << "Invalid choice" << endl;
                mainGame(players, gameBoard);
            }
        }
    }
    // FIN DE LA BOUCLE X9
    // Utilisation des bonus
    cout << " ---------------------------------" << endl;
    for (int i = 0; i < players.size(); ++i) {
        cout << "Player :"<<players[i].getName() << endl;
        cout << " You will use all of your bonus" << endl;
        cout << "You have " << players[i].getTileExchange() << " tile exchange" << endl;
        cout << "So you can transform " << players[i].getTileExchange() <<  " cases with nothing into a case with your color" << endl;
        cout << " ---------------------------------" << endl;
        for (int i = 0 ; i < players[i].getTileExchange(); ++i) {
            cout <<"Where would you want to give your color ?" << endl;
            int x,y ;
            cin >> x >> y;
            x -= 1;
            y -= 1;
            gameBoard.tileExchangeStone(players[i].getPlayerValue(),true,x,y);
        }
        cout << "Now you have placed all of your bonus" << endl;
        cout << "We will now see the result of the game" << endl;

        int maxSquareSize = 0;
        int maxGrassCount = 0;
        player* winner = nullptr;
        for (auto& p : players) {
            int squareSize = gameBoard.isSquare(p.getPlayerValue());
            int grassCount = gameBoard.howManyGrass(p.getPlayerValue());
            if (squareSize > maxSquareSize || (squareSize == maxSquareSize && grassCount > maxGrassCount)) {
                maxSquareSize = squareSize;
                maxGrassCount = grassCount;
                winner = &p;
            }
        }
        cout <<" And the winner is " << endl;
        this_thread::sleep_for(chrono::seconds(3));
        if (winner) {
            cout << winner->getName() << " with a square size of " << maxSquareSize << " and " << maxGrassCount << " grass blocks." << endl;
        } else {
            cout << "No winner could be determined." << endl;
        }
    }
}
void display::exchangedTile(board& gameBoard,player p,vector<player> players) {
    cout << " ---------------------------------" << endl;
    cout << "Exchange Tile (1)" << endl;
    cout << "Swap Stone to grass (2)" << endl;
    cout << "Get Back to main game (3)" << endl;
    cout << " ---------------------------------" << endl;
    int playerChoice ;
    cin >> playerChoice;
    if (playerChoice == 1) {
        if (p.getTileExchange() >= 1) {
            cout <<"What piece do you want to go to "<<endl;
            int i ;
            cin >> i;
            i -= 1;
            tileExchangeList(i);
            p.useTileExchange();
            mainGame(players, gameBoard);
        }
    }
    else if (playerChoice == 2) {
        if (p.getTileExchange() >= 1) {
            for (int i=0 ; i < gameBoard.grid.size() ; ++i) {
                for (int j=0 ; j < gameBoard.grid[i].size() ; ++j) {
                    if (gameBoard.grid[i][j].GetValue() == 15) {
                        cout << "Where would you want to take a stone ?" << endl;
                        int x, y;
                        cin >> x >> y;
                        x -= 1;
                        y -= 1;
                        gameBoard.tileExchangeStone(p.getPlayerValue(),false,x,y);
                        p.useTileExchange();
                        mainGame(players, gameBoard);
                    }
                    else {
                        cout << "You don't have any stone to exchange." << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        mainGame(players, gameBoard);
                    }
                }
            }
        }else{
            cout << "You don't have any tile to exchange." << endl;
            mainGame(players, gameBoard);
        }
    }else if (playerChoice == 3) {
        mainGame(players, gameBoard);
    }else {
        cout << "Invalid choice" << endl;
        exchangedTile(gameBoard, p,players);
    }
}
void display::tileExchangeList (int x){
    /*
     * déplace une pièce dans la liste à la position choisit par le joueur
     **/
    vector<string> listTemp = pieceList;
    if (x > 0 && x < listTemp.size()) {
        std::vector<std::string> temp(listTemp.begin(), listTemp.begin() + x);
        listTemp.erase(listTemp.begin(), listTemp.begin() + x);
        listTemp.insert(listTemp.end(), temp.begin(), temp.end());
    }
    pieceList = listTemp;
    for (int i = 0; i < 5; ++i) {
        cout << pieceList[i] << endl;
    }
}
void display::takeTile(board& gameBoard, player p,vector<player> players, int nbPlayer, std::vector<std::vector<int>> piece, int turnCount) {
    int playerChoice ;
    tetris Tetris;
    cout << " ---------------------------------" << endl;
    cout <<"Tile to place" << endl;
    Tetris.displayPiece(piece);
    cout << " ---------------------------------" << endl;
    cout <<" Flip Tile (1)" << endl;
    cout <<" Rotate Tile (2)" << endl;
    cout <<" Place Tile (3)" << endl;
    cout <<" Get Back to main game (4)" << endl;
    cout << " ---------------------------------" << endl;
    cin >> playerChoice;
    if (playerChoice == 1) {
        piece = Tetris.getFlipPiece(piece);
        takeTile(gameBoard, p,players, nbPlayer, piece, turnCount);
    }
    else if (playerChoice == 2) {
        piece = Tetris.getRotatePiece(piece);
        takeTile(gameBoard, p,players, nbPlayer, piece, turnCount);
    }
    else if (playerChoice == 3) {
        putTile(gameBoard, p, nbPlayer, piece, turnCount);
    }
    else if (playerChoice == 4) {
        mainGame(players, gameBoard);
    }
    else {
        cout << "Invalid choice" << endl;
        takeTile(gameBoard, p,players, nbPlayer, piece, turnCount);
    }
}
void display::putTile(board& gameBoard, player p, int nbPlayer, vector<vector<int>> piece, int turnCount) {
    int x, y;
    tetris Tetris;
    Tetris.displayPiece(piece);
    cout << " ---------------------------------" << endl;
    cout << "Please, choose the position (x y) : ";
    cout << "Line (most top-left square of the tile)" << endl;
    cout << "Column (most top-left square of the tile)" << endl;
    cin >> x >> y;
    x -= 1;
    y -= 1;
    if(gameBoard.piecePlacementVerif(x,y,piece,p.getPlayerValue())) {
        isTakeTileFinish = true;
        gameBoard.piecePlace(x, y, piece, p.getPlayerValue(),turnCount);
    }
    else {
        putTile(gameBoard, p, nbPlayer, piece, turnCount);
    }
}
void display::boardColor(vector<player> players, const board& gameBoard) {
    cout << "   ";
    for (int j = 0; j < gameBoard.grid[0].size(); ++j) {
        cout << static_cast<char>('A' + j) << " ";
    }
    cout << std::endl;
    for (int i = 0; i < gameBoard.grid.size(); ++i) {
        cout << static_cast<char>('A' + i) << "  ";
        for (int j = 0; j < gameBoard.grid[i].size(); ++j) {
            int value = gameBoard.grid[i][j].GetValue();
            char turn = gameBoard.grid[i][j].GetTurn();
            vector<pair<int, string>> colors = players[value - 1].setColor();
            if (value >= 1 && value < 10) {
                cout << colors[players[value - 1].getColor()].second << gameBoard.grid[i][j].GetTurn() << colors[0].second << " ";
            } else {
                switch (value) {
                    case 10:
                        cout << colors[10].second << "E" << colors[0].second << " ";
                    break;
                    case 11:
                        cout << colors[10].second << "S" << colors[0].second << " ";
                    break;
                    case 12:
                        cout << colors[10].second << "V" << colors[0].second << " ";
                    break;
                    case 15:
                        cout << colors[10].second << "X" << colors[0].second << " ";
                    break;
                    default:
                        cout << ". ";
                    break;
                }
            }
        }
        cout << endl;
    }
}
