#include "joueur.hpp"

Joueur::~Joueur() {}

int Joueur::subPvBase(int atq) {
	int res = pvBase;
	if (pvBase >= atq) {
		pvBase -= atq;
		return atq;
	} else {
		pvBase = 0;
		return res;
	}
}