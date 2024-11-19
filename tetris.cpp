#include <filesystem>
#include <fstream>
#include <iostream>
#include "tetris.h"

#include <random>

#include "display.h"
#include "json.hpp"
#include <stdlib.h>
#include <time.h>
using json = nlohmann::json;
using namespace std;


tetris::tetris() = default;
void tetris::displayPiece(const std::vector<std::vector<int>>& piece) {
    /*
     *affichage des pieces dans la console
     **/
    for (const auto& row : piece) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}



/*
 *std::vector<std::vector<int>> tetris::getPieceTetris(const json& pieces, const std::string& nom_piece) {
    std::vector<std::vector<int>> piece;

    if (pieces.contains(nom_piece)) {
        for (const auto& row : pieces[nom_piece]) {
            std::vector<int> rowVector;
            for (int cell : row) {
                rowVector.push_back(cell);
            }
            piece.push_back(rowVector);
        }
    } else {
        std::cerr << "Erreur : La pièce '" << nom_piece << "' n'existe pas dans le JSON.\n";
    }

    return piece;
}
*/
std::vector<std::vector<int>> tetris::getPieceTetrisEasy(const std::string &nom_piece) {
    /*
     * *chargement d'une piece depuis le JSON
     *affiche la piece si elle existe, sinon affiche une erreur
     **/
    std::ifstream f("../tetrisFile.json");
    if (!f) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier JSON\n";
    }
    try {
        json data;
        f >> data;
        if (data.contains("pieces")) {
            auto pieces = data["pieces"];

            std::vector<std::vector<int>> piece;

            if (pieces.contains(nom_piece)) {
                for (const auto& row : pieces[nom_piece]) {
                    std::vector<int> rowVector;
                    for (int cell : row) {
                        rowVector.push_back(cell);
                    }
                    piece.push_back(rowVector);
                }
            } else {
                std::cerr << "Erreur : La pièce '" << nom_piece << "' n'existe pas dans le JSON.\n";
            }
            f.close();
            return piece;
        }
    }catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "Erreur de type JSON : " << e.what() << std::endl;
    }
}
/*
 *void tetris::loadJson(string nom_piece) {
    // Charger le fichier JSON
    std::ifstream f("../tetrisFile.json");
    if (!f) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier JSON\n";
    }

    try {
        json data;
        f >> data;
        // Vérifier que la clé "pieces" existe
        if (data.contains("pieces")) {
            auto pieces = data["pieces"];
            // afficherPieceTetris(pieces, nom_piece);
            displayPiece(getPieceTetris(pieces, nom_piece));
        } else {
            std::cerr << "Erreur : La clé 'pieces' n'existe pas dans le JSON.\n";
        }
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "Erreur de type JSON : " << e.what() << std::endl;
    }

    f.close();
}
*/
std::vector<std::vector<int>> tetris::getRotatePiece(const std::vector<std::vector<int>>& piece) {
    /*
     *rotation d'une piece
     *renvoie une nouvelle piece apres rotation
     **/
    std::vector<std::vector<int>> newPiece;
    for (int i = 0; i < piece[0].size(); ++i) {
        std::vector<int> row;
        for (int j = piece.size() - 1; j >= 0; --j) {
            row.push_back(piece[j][i]);
        }
        newPiece.push_back(row);
    }
    return newPiece;
}
std::vector<std::vector<int>> tetris::getFlipPiece(const std::vector<std::vector<int>>& piece) {
    /*
     *inversion d'une piece
     *renvoie une nouvelle piece apres inversion
     **/
    std::vector<std::vector<int>> newPiece;
    for (int i = piece.size() - 1; i >= 0; --i) {
        std::vector<int> row;
        for (int j = 0; j < piece[i].size(); ++j) {
            row.push_back(piece[i][j]);
        }
        newPiece.push_back(row);
    }
    return newPiece;
}
vector<string> tetris::generateRandomPieceList(int numberOfPlayers) {
    /*
     *generation d'une liste de pieces aleatoires selon le nombre de joueurs
     *renvoie une liste de pieces
     **/
    std::ifstream f("../tetrisFile.json");
    if (!f) {
        std::cerr << "Error: Unable to open JSON file\n";
        return {};
    }
    nlohmann::json data;
    f >> data;
    f.close();

    std::vector<std::string> availablePieces;
    if (data.contains("pieces")) {
        for (auto& piece : data["pieces"].items()) {
            availablePieces.push_back(piece.key());
        }
    } else {
        std::cerr << "Error: 'pieces' key not found in JSON\n";
        return {};
    }

    int listSize = static_cast<int>(std::ceil(numberOfPlayers * 10.67));
    std::vector<std::string> pieceList;
    std::default_random_engine generator(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> distribution(0, availablePieces.size() - 1);

    for (int i = 0; i < listSize; ++i) {
        int randomIndex = distribution(generator);
        pieceList.push_back(availablePieces[randomIndex]);
    }

    return pieceList;
}
