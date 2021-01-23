#include "fantassin.hpp"

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}

std::pair<bool,std::vector<int>> Fantassin::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    int positionCible = i + getCamp() * getPortee();
    if (! (plateau[positionCible] == nullptr) ) {
        if (plateau[positionCible]->getCamp() != getCamp()) {
            afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCible], positionCible);
            plateau[positionCible]->subPV(atq);
            autreAction = false;
            if (aVaincuFantassin(plateau[positionCible])) {
                return std::make_pair(true, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
            else if (plateau[positionCible]->estVaincu()) {
                return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        afficheAttaqueBase(this, getNomUnite(), atq, i);
        joueur->subPvBase(atq);
    }
    return std::make_pair(false, std::vector<int>()={});
}

bool Fantassin::aVaincuFantassin(Unite* unite) { //si je mets que Unite unite ca marche pas... il veut un pointeur ce shlag
    if ( unite->estVaincu() && (unite->getNomUnite() == 'F') ) {
        return true;
    }
    else {
        return false;
    }
}