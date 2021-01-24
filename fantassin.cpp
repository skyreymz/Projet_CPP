#include "fantassin.hpp"
#include "superSoldat.hpp"

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}

std::vector<int> Fantassin::attaque(Unite* plateau[12], int i, Joueur* joueur) {
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
            pvRetire = plateau[positionCible]->subPV(atq);
            afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
            setAutreAction(false);

            if (plateau[positionCible]->estVaincu()) {
                if (aVaincuFantassin(plateau[positionCible])) {
                    // On évolue le fantassin s'il a vaincu un fantassin ennemi
				    int pv = plateau[i]->getPV();
                    int camp = plateau[i]->getCamp(); 
				    delete plateau[i];
				    plateau[i] = new SuperSoldat(camp, pv);
                }
                return std::vector<int>(1)={positionCible};
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        pvRetire = joueur->subPvBase(atq);
        afficheAttaqueBase(getNomUnite(), pvRetire, i);
        setAutreAction(false);
    }
    return std::vector<int>()={};
}

bool Fantassin::aVaincuFantassin(Unite* unite) { 
    if (unite->getNomUnite() == 'F') {
        return true;
    }
    else {
        return false;
    }
}

void Fantassin::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new Fantassin(plateau[i]->getCamp(), plateau[i]->getPV(), plateau[i]->getAutreAction());
	std::cout << "F(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}