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
 * Permet l'affichage du type de l'unité et de son camp
 * 
 * @param flux : ostream& 
 * @param u : const Unite&
 * @return ????????????????
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