#include <iostream>
#include "fantassin.hpp"
#include <string>
#include <typeinfo>

int Fantassin::prix = 10;
int Fantassin::atq = 4;
//int Fantassin::portee = {1};

Fantassin::~Fantassin() {}

std::string Fantassin::getInfos() const {
	return "F("+Unite::getInfos()+")";
}

// à voir si cette fonction va plutôt dans la classe aireDeJeu...
bool Fantassin::aVaincuFantassin(Unite* unite) { //si je mets que Unite unite ca marche pas... il veut un pointeur ce shlag
    Fantassin f = Fantassin(0); // uniquement pour la comparaison des noms
    if ( (typeid(unite).name() == typeid(f).name()/*"9Fantassin"*/) && unite->estVaincu() ) {
        return true;
    }
    else {
        return false;
    }
}

int Fantassin::getPrix() {
    return prix;
}
