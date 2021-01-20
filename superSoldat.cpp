#include <iostream>
#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}

bool SuperSoldat::getAutreAction() {
    return autreAction;
}


//IL FAUDRA CHANGER LE bool camp en int = 1 ou -1
std::pair<bool,std::vector<int>> SuperSoldat::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    if (! (plateau[i + getCamp()] == nullptr) ) {
        if (plateau[i + getCamp()]->getCamp() != getCamp()) {
            plateau[i + getCamp()]->setPV(- Fantassin::getAtq());
            
            if (plateau[i + getCamp()]->estVaincu()) {
            	return std::make_pair(false, std::vector<int>(1)={i+ getCamp()});
            }
        }
    }
    else if ( (i + getCamp() * getPortee()) == indiceMAX ) {
        joueur->setPvBase(- Fantassin::getAtq());
    }
    return std::make_pair(false, std::vector<int>()={});
}