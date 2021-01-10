#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include <array>
#include "unite.hpp"

class AireDeJeu {
	
	Unite* plateau[12]; // est ce une solution viable ? On ne sait pas si en C++, un fantassin sera considere comme une unite et pas plus...
	int tourDeJeu; // 0 ou 1, permet de differencier le joueur de gauche de celui de droite
	int nbToursMAX;
	
	
	public:
		AireDeJeu(int nbToursMaximum = 100) : nbToursMAX(nbToursMaximum), plateau() {} // initialise un tableau de pointeurs avec des pointeurs null
		
		~AireDeJeu();

		// Pour gerer le plateau :
		// - retirer une Unite du plateau : delete plateau[element];
		// - s'il n'y a pas d'Unite sur la case du plateau : try catch des null pointers
		
		
};

#endif
