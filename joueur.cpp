#include "joueur.hpp"

Joueur::~Joueur() {}

/**
 * Soutrait Joueur::pvBase par la valeur de atq si l'attaque est inférieure à Joueur::pv
 * Met Joueur::pvBase à 0 sinon
 *
 * @param atq la quantité de points de vie soustraite
 * @return atq si atq est strictement inférieure à Joueur::pvBase, -1 sinon
  */
int Joueur::subPvBase(int atq) {
	if (pvBase > atq) {
		pvBase -= atq;
		return atq;
	} else {
		pvBase = 0;
		return -1;
	}
}