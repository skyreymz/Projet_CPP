#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include "unite.hpp"
#include "fantassin.hpp"
#include "archer.hpp"
#include "catapulte.hpp"
#include "superSoldat.hpp"
#include "joueur.hpp"

class AireDeJeu {
	public: // j'ai mis ça pour ajouter plus facilement pour les tests, faudra le supprimer
	Unite* plateau[12];
	int tourDeJeu; // 1 ou -1, permet de differencier le joueur de gauche de celui de droite
	int nbToursActuel;
	int nbToursMAX;

	Joueur jA;
	Joueur jB;
	
	public:
		AireDeJeu(bool mod, int tourActuel = 1, int tourMaximum = 100);

		~AireDeJeu();

		bool charger(char* entree);
		bool sauvegarder(char* sortie) const;
		void setAireDeJeu(int tourDeJeu0, int nbToursActuel0, int nbToursMAX0){tourDeJeu = tourDeJeu0; nbToursActuel = nbToursActuel0; nbToursMAX = nbToursMAX0;};

		void print() const;
		bool finDeJeu() const;

		void nouveauTour();
		void creationUniteManuelle(bool joueur);
		
		void jouerActions();
		void finTour();
		
};

#endif
