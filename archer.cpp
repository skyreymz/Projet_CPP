#include "archer.hpp"

int Archer::prix = 12;
int Archer::atq = 3;
int Archer::portee[3] = {1,2,3};

Archer::~Archer() {}

std::vector<int> Archer::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    bool attaqueRealisee = false;
    for (int j=0; (j<3) && !attaqueRealisee; j++) {
        int positionCible = i + getCamp() * portee[j];
        int pvRetire;
        if (plateau[positionCible] != nullptr) {
            if (plateau[positionCible]->getCamp() != getCamp()) {
                pvRetire = plateau[positionCible]->subPV(atq);
                afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
                if (plateau[positionCible]->estVaincu()) {
                    return std::vector<int>(1)={i+ getCamp() * portee[j]};
                }
                attaqueRealisee = true;
            }
        }
        else if ( positionCible == indiceMAX ) {
            pvRetire = joueur->subPvBase(atq);
            afficheAttaqueBase(getNomUnite(), pvRetire, i);
            attaqueRealisee = true;
        }
    }
    return std::vector<int>()={};
}

void Archer::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new Archer(plateau[i]->getCamp(), plateau[i]->getPV());
	std::cout << *(plateau[i]) << "(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}