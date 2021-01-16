#include <iostream>
#include "fantassin.hpp"
#include <string>
#include <typeinfo>

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}

std::string Fantassin::getInfos() const {
	return "F("+Unite::getInfos()+")";
}

// à voir si cette fonction va plutôt dans la classe aireDeJeu...
bool Fantassin::aVaincuFantassin(Unite* unite) { //si je mets que Unite unite ca marche pas... il veut un pointeur ce shlag
    Fantassin f = Fantassin(0); // uniquement pour la comparaison des noms
    if ( unite->estVaincu() && (typeid(unite).name() == typeid(f).name()/*"9Fantassin"*/) ) {
        return true;
    }
    else {
        return false;
    }
}

int Fantassin::getPrix() {
    return prix;
}


//IL FAUDRA CHANGER LE bool camp en int = 1 ou -1
// ne pas oublier de donner de l'argent au joueur lorsqu'une unité meurt
std::pair<bool,std::vector<int>> Fantassin::attaque(Unite* plateau[12], int i) {
    if (! (plateau[i + getCamp() * portee[0]] == nullptr) ) {
        if (plateau[i + getCamp() * portee[0]]->getCamp() != getCamp()) {
            plateau[i+ getCamp() * portee[0]]->setPV(-atq);
            if (aVaincuFantassin(plateau[i + getCamp() * portee[0]])) {
                return std::make_pair(true, std::vector<int>(1)={i+ getCamp() * portee[0]});
            }
        }
    }
    return std::make_pair(false, std::vector<int>()={});
}
