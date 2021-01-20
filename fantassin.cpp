#include <iostream>
#include "fantassin.hpp"
#include <string>
#include <typeinfo>

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}


bool Fantassin::aVaincuFantassin(Unite* unite) { //si je mets que Unite unite ca marche pas... il veut un pointeur ce shlag
    if ( unite->estVaincu() && (unite->getNomUnite() == 'F') ) {
        return true;
    }
    else {
        return false;
    }
}


std::pair<bool,std::vector<int>> Fantassin::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    char camp;
    char campEnnemi;
    if (getCamp() == 1) {
        indiceMAX = 11;
        camp = 'A';
        campEnnemi = 'B';
    }
    else {
        indiceMAX = 0;
        camp = 'B';
        campEnnemi = 'A';
    }

    Unite* cible = plateau[i + getCamp() * getPortee()];
    if (! (cible == nullptr) ) {
        if (cible->getCamp() != getCamp()) {
            std::cout << "F(" << camp << ") a attaqué " << cible->getNomUnite() << '(' << campEnnemi << ')' << std::endl;
            cible->setPV(-atq);
            if (aVaincuFantassin(plateau[i + getCamp() * getPortee()])) {
                return std::make_pair(true, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
            else if (plateau[i + getCamp() * getPortee()]->estVaincu()) {
                return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
        }
    }
    else if ( (i + getCamp() * getPortee()) == indiceMAX ) {
        joueur->setPvBase(-atq);
    }
    return std::make_pair(false, std::vector<int>()={});
}
