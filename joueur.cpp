#include <iostream>
#include "joueur.hpp"

Joueur::~Joueur() {}

int Joueur::getArgent() const {
	return argent;
}

void Joueur::setArgent(int money) {
	argent += money;
}


void Joueur::dommages(int atq) {
	pvBase -= atq;
}