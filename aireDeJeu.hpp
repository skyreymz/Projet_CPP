#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include <array>
#include "unite.hpp"
#include "joueur.hpp"

class AireDeJeu {
	
	Unite* plateau[12]; // est ce une solution viable ? On ne sait pas si en C++, un fantassin sera considere comme une unite et pas plus...
	int tourDeJeu; // 0 ou 1, permet de differencier le joueur de gauche de celui de droite
	int nbToursActuel;
	int nbToursMAX;

	Joueur* j1;
	Joueur* j2;
	
	public:
		AireDeJeu(int tourActuel = 0, int tourMaximum = 100, bool mode) : plateau(), tourDeJeu(0), nbToursActuel(tourActuel), nbToursMAX(tourMaximum), j1(new Joueur(0, 50)), j2(new Joueur(mode, 50)) {} // initialise un tableau de pointeurs avec des pointeurs null
		
		~AireDeJeu();

		void print() const;

		// Pour gerer le plateau :
		// - retirer une Unite du plateau : delete plateau[element];
		// - s'il n'y a pas d'Unite sur la case du plateau : try catch des null pointers
		
		
};

#endif
