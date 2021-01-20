#include <iostream>
#include "joueur.hpp"

Joueur::~Joueur() {}

void Joueur::setPvBase(int atq) {
	if ((pvBase+atq) >= 0) {
		pvBase += atq;
	} else {
		pvBase = 0;
	}
}