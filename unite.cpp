#include "unite.hpp"

Unite::~Unite() {}

char Unite::getCampChar() const{
	if (camp == 1) {
		return 'A';
	} else {
		return 'B';
	}
}


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