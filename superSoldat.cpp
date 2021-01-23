#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}


std::vector<int> SuperSoldat::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    int positionCible = i + getCamp() * getPortee();
    if (plateau[positionCible] != nullptr) {
        if (plateau[positionCible]->getCamp() != getCamp()) {
            afficheAttaqueUnite(this, getNomUnite(), Fantassin::getAtq(), i, plateau[positionCible], positionCible);
            plateau[positionCible]->subPV(Fantassin::getAtq());
            
            if (plateau[positionCible]->estVaincu()) {
            	return std::vector<int>(1)={i+ getCamp()};
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        afficheAttaqueBase(this, getNomUnite(), Fantassin::getAtq(), i);
        joueur->subPvBase(Fantassin::getAtq());
    }
    return std::vector<int>()={};
}

void SuperSoldat::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new SuperSoldat(plateau[i]->getPV(), plateau[i]->getCamp());
	std::cout << "S(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}