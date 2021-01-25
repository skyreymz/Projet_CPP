#include "unite.hpp"

Unite::~Unite() {}

/**
 * Permet d'obtenir un caractère utile à l'affichage en fonction du camp de l'unité
 * 
 * @return un caractère représentant une équipe
 */
char Unite::getCampChar() const{
	if (camp == 1) {
		return 'A';
	} else {
		return 'B';
	}
}

/**
 * Surcharge de l'opérateur <<
 * Stockage de la première lettre de la classe de l'unité ainsi que son camp
 * pour permettre l'affichage
 * 
 * @param &flux reçoit les informations
 * @param &u une référence de l'instance à traiter
 * @return &flux
 */
std::ostream &operator<<(std::ostream &flux, const Unite &u) {
	char campChar;
	if (u.getCamp() == 1) {
		campChar = 'A';
	} else {
		campChar = 'B';
	}
	flux << u.getNomUnite() << '(' << campChar << ')';
	return flux;
}

/**
 * Soutrait pv par la valeur de atq si l'attaque est inférieure à pv, met pv à 0 sinon
 *
 * @param atq la quantité de points de vie soustraite
 * @return atq si atq est strictement inférieure à pv, -1 sinon
 */
int Unite::subPV(int atq) {
	if (pv > atq) {
		pv -= atq;
		return atq;
	} else {
		pv = 0;
		return -1;
	}
}

void Unite::afficheAttaqueUnite(char nomUnite, int atq, int position, Unite* cible, int positionCible) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ')';
	if (atq != -1) {
	 std::cout << " a enlevé " << atq << "PV à ";
	} else {
		std::cout << " a tué ";
	}
	 std::cout << *cible << "(position " << positionCible << ")\n";
}

void Unite::afficheAttaqueBase(char nomUnite, int atq, int position) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ')';
	if (atq != -1) {
	 std::cout << " a enlevé " << atq << "PV à ";
	} else {
		std::cout << " a détruit ";
	}
	std::cout << "la Base du joueur " << char(getCampChar()+camp) << std::endl;
}