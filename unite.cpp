#include "unite.hpp"

Unite::~Unite() {}

char Unite::getCampChar() const{
	if (camp == 1) {
		return 'A';
	} else {
		return 'B';
	}
}

void Unite::afficheAttaqueUnite(char nomUnite, int atq, int position, Unite* cible, int positionCible) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ") a enlevé " << atq << "PV à " << cible->getNomUnite() << '(' << cible->getCampChar() << ")(position " << positionCible << ")\n";
}

void Unite::afficheAttaqueBase(char nomUnite, int atq, int position) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ") a enlevé " << atq << "PV à la Base du joueur " << char(getCampChar()+camp) << std::endl;
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