#include "joueur.hpp"

Joueur::~Joueur() {}

void Joueur::subPvBase(int atq) {
	if ((pvBase - atq) >= 0) {
		pvBase -= atq;
	} else {
		pvBase = 0;
	}
}