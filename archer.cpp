#include "archer.hpp"

int Archer::prix = 12;
int Archer::atq = 3;
int Archer::portee[3] = {1,2,3};

Archer::~Archer() {}

std::pair<bool,std::vector<int>> Archer::attaque(Unite* plateau[12], int i, Joueur* joueur) {
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
                afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
                if (plateau[positionCible]->estVaincu()) {
                    return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * portee[j]});
                }
                attaqueRealisee = true;
            }
        }
        else if ( positionCible == indiceMAX ) {
            pvRetire = joueur->subPvBase(atq);
            afficheAttaqueBase(this, getNomUnite(), pvRetire, i);
            attaqueRealisee = true;
        }
    }
    return std::make_pair(false, std::vector<int>()={});
}