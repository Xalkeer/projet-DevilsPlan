#include <filesystem>
#include <fstream>
#include <iostream>

#include "tetris.h"
#include "json.hpp"


using json = nlohmann::json;
using namespace std;


tetris::tetris(int PlayerValue): PlayerValue(PlayerValue) {}
void afficherPieceTetris(const json& pieces, const std::string& nom_piece) {

    if (pieces.contains(nom_piece)) {
        std::cout << "Nom de la pièce : " << nom_piece << std::endl;
        for (const auto& row : pieces[nom_piece]) {
            for (int cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Erreur : La pièce '" << nom_piece << "' n'existe pas dans le JSON.\n";
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
            afficherPieceTetris(pieces, nom_piece);
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



