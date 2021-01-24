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
    int pvRetire;
    if (plateau[positionCible] != nullptr) {
        if (plateau[positionCible]->getCamp() != getCamp()) {
            pvRetire = plateau[positionCible]->subPV(Fantassin::getAtq());
            afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
            
            if (plateau[positionCible]->estVaincu()) {
            	return std::vector<int>(1)={i+ getCamp()};
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        pvRetire = joueur->subPvBase(Fantassin::getAtq());
        afficheAttaqueBase(getNomUnite(), pvRetire, i);
    }
    return std::vector<int>()={};
}

void SuperSoldat::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new SuperSoldat(plateau[i]->getCamp(), plateau[i]->getPV());
	std::cout << *(plateau[i]) << "(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}