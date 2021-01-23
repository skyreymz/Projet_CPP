#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}

bool SuperSoldat::getAutreAction() {
    return autreAction;
}

std::pair<bool,std::vector<int>> SuperSoldat::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    int positionCible = i + getCamp() * getPortee();
    int pvRetire;
    if (plateau[positionCible] != nullptr) {
        if (plateau[positionCible]->getCamp() != getCamp()) {
            pvRetire = plateau[positionCible]->subPV(Fantassin::getAtq());
            afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
            
            if (plateau[positionCible]->estVaincu()) {
            	return std::make_pair(false, std::vector<int>(1)={i+ getCamp()});
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        pvRetire = joueur->subPvBase(Fantassin::getAtq());
        afficheAttaqueBase(this, getNomUnite(), pvRetire, i);
    }
    return std::make_pair(false, std::vector<int>()={});
}