#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include <array>
#include "unite.hpp"
#include "fantassin.hpp"
#include "archer.hpp"
#include "catapulte.hpp"
#include "superSoldat.hpp"
#include "joueur.hpp"

class AireDeJeu {
	public: // j'ai mis ça pour ajouter plus facilement pour les tests, faudra le supprimer
	Unite* plateau[12]; // est ce une solution viable ? On ne sait pas si en C++, un fantassin sera considere comme une unite et pas plus...
	int tourDeJeu; // 0 ou 1, permet de differencier le joueur de gauche de celui de droite
	int nbToursActuel;
	int nbToursMAX;

	bool mode; // mode du joueur B : 0 signifie manuel ; 1 signifie automatique
	Joueur jA;
	Joueur jB;
	
	public:
		AireDeJeu(int tourActuel = 0, int tourMaximum = 100, bool mod = 0) : plateau(), tourDeJeu(0), nbToursActuel(tourActuel), nbToursMAX(tourMaximum), mode(mod), jA(Joueur(0, 50)), jB(Joueur(mod, 50)) {} // initialise un tableau de pointeurs avec des pointeurs null
		
		~AireDeJeu();

		void print() const;

		void nouveauTour();
		void creationUniteManuelle(bool joueur);

		// Pour gerer le plateau :
		// - retirer une Unite du plateau : delete plateau[element];
		// - s'il n'y a pas d'Unite sur la case du plateau : try catch des null pointers
		
		
};

#endif
