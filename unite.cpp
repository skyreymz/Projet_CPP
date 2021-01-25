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
 * @param &u une référence de l'Unite à traiter
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
 * Soutrait Unite::pv par la valeur de atq si l'attaque est inférieure à Unite::pv
 * Met Unite::pv à 0 sinon
 *
 * @param atq les points d'attaque de l'unité
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

/**
 * Affichage des caractéristiques de l'attaque de l'unité envers une autre unité
 *
 * @param1 nomUnite le premier caractère de la classe de l'unité courante
 * @param2 atq les points d'attaques de l'Unite courante
 * @param3 position entier correspondant à l'indice de l'Unite courante en jeu
 * @param4 *cible pointeur sur l'Unité subissant l'attaque
 * @param5 positionCible entier correspondant à l'indice de l'Unite cible en jeu
 */
void Unite::afficheAttaqueUnite(char nomUnite, int atq, int position, Unite* cible, int positionCible) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ')';
	if (atq != -1) {
	 std::cout << " a enlevé " << atq << "PV à ";
	} else {
		std::cout << " a tué ";
	}
	 std::cout << *cible << "(position " << positionCible << ")\n";
}

/**
 * Affichage des caractéristiques de l'attaque de l'unité envers la base ennemie
 *
 * @param1 nomUnite le premier caractère de la classe de l'Unité courante
 * @param2 atq les points d'attaques de l'Unite courante
 * @param3 position entier correspondant à l'indice de l'Unite courante en jeu
 */
void Unite::afficheAttaqueBase(char nomUnite, int atq, int position) const{
	std::cout << nomUnite << '(' << getCampChar() << ")(position " << position << ')';
	if (atq != -1) {
	 std::cout << " a enlevé " << atq << "PV à ";
	} else {
		std::cout << " a détruit ";
	}
	std::cout << "la Base du joueur " << char(getCampChar()+camp) << std::endl;
}