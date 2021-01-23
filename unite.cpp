#include "unite.hpp"

Unite::~Unite() {}

char Unite::getCampChar() const{
	if (camp == 1) {
		return 'A';
	} else {
		return 'B';
	}
}

char Unite::getCampEnnemiChar() const{
	if (camp == 1) {
		return 'B';
	} else {
		return 'A';
	}
}

void Unite::afficheAttaqueUnite(Unite* emetteur, char nomUnite, int atq, int position, Unite* cible, int positionCible) const{
	std::cout << nomUnite << '(' << emetteur->getCampChar() << ")(position " << position << ") a enlevé " << atq << "PV à " << cible->getNomUnite() << '(' << cible->getCampChar() << ")(position " << positionCible << ")\n";
}

void Unite::afficheAttaqueBase(Unite* emetteur, char nomUnite, int atq, int position) const{
	std::cout << nomUnite << '(' << emetteur->getCampChar() << ")(position " << position << ") a enlevé " << atq << "PV à la Base du joueur " << getCampEnnemiChar() << std::endl;
}

int Unite::subPV(int atq) {
	int res = pv;
	if (pv >= atq) {
		pv -= atq;
		return atq;
	} else {
		pv = 0;
		return res;
	}
}