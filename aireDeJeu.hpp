#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include <array>
#include "unite.hpp"
#include "joueur.hpp"

class AireDeJeu {
	
	Unite* plateau[12]; // est ce une solution viable ? On ne sait pas si en C++, un fantassin sera considere comme une unite et pas plus...
	int tourDeJeu; // 1 ou -1, permet de differencier le joueur de gauche de celui de droite
	int nbToursActuel;
	int nbToursMAX;

	Joueur* j1;
	Joueur* j2;
	
	public:
		AireDeJeu(bool mode, int tourMaximum = 100);
		~AireDeJeu();

		void print() const;

		// Pour gerer le plateau :
		// - retirer une Unite du plateau : delete plateau[element]; plateau[element] = NULL;
		// - s'il n'y a pas d'Unite sur la case du plateau : try catch des null pointers
		
		void jouerTour();
		
};

#endif
