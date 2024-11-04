#include <fstream>
#include <iostream>

#include "board.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Fonction pour récupérer et afficher une seule pièce de Tetris
void afficherPieceTetris(const json& pieces, const std::string& nom_piece) {
    // Vérifier si la pièce existe dans le JSON
    if (pieces.contains(nom_piece)) {
        std::cout << "Nom de la pièce : " << nom_piece << std::endl;

        // Récupérer et afficher la matrice de la pièce
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

int main() {
    board a(5);
    a.displayGrid();


    // Charger le fichier JSON
    std::ifstream f("../tetrisFile.json");
    if (!f) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier JSON\n";
        return 1;
    }

    try {
        json data;
        f >> data;

        // Vérifier que la clé "pieces" existe
        if (data.contains("pieces")) {
            auto pieces = data["pieces"];

            // Nom de la pièce que vous souhaitez récupérer
            std::string nom_piece = "Tetris02";  // Par exemple, "Tetris2"

            // Afficher la pièce de Tetris demandée
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
    return 0;
}
