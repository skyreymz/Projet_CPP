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


std::pair<bool,std::vector<int>> Fantassin::attaque(Unite* plateau[12], int i) {
    if (! (plateau[i + getCamp() * getPortee()] == nullptr) ) {
        if (plateau[i + getCamp() * getPortee()]->getCamp() != getCamp()) {
            plateau[i + getCamp() * getPortee()]->setPV(-atq);
            if (aVaincuFantassin(plateau[i + getCamp() * getPortee()])) {
                return std::make_pair(true, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
            else if (plateau[i + getCamp() * getPortee()]->estVaincu()) {
                return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
        }
    }
    return std::make_pair(false, std::vector<int>()={});
}
