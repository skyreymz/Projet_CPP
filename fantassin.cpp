#include <iostream>
#include "fantassin.hpp"
#include <typeinfo>

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}

// à voir si cette fonction va plutôt dans la classe aireDeJeu...
bool Fantassin::aVaincuFantassin(Unite* unite) { //si je mets que Unite unite ca marche pas... il veut un pointeur ce shlag
    if ( (typeid(unite).name() == "9Fantassin") && unite->estVaincu() ) {
        return true;
    }
    else {
        return false;
    }
}

int Fantassin::getPrix() {
    return prix;
}
