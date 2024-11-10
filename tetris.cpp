#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include "tetris.h"

#include "display.h"
#include "json.hpp"


using json = nlohmann::json;
using namespace std;
tetris::tetris(int PlayerValue): PlayerValue(PlayerValue) {}

void tetris::displayPiece(const std::vector<std::vector<int>>& piece) {
    for (const auto& row : piece) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> tetris::getPieceTetris(const json& pieces, const std::string& nom_piece) {
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

std::vector<std::vector<int>> tetris::getPieceTetrisEasy(const std::string &nom_piece) {
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

            return piece;

        }
    }catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "Erreur de type JSON : " << e.what() << std::endl;
    }
}

void tetris::loadJson(string nom_piece) {
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

std::vector<std::vector<int>> tetris::getRotatePiece(const std::vector<std::vector<int>>& piece) {
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
