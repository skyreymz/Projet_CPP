#ifndef AIREDEJEU_HPP
#define AIREDEJEU_HPP

#include <iostream>
#include "joueur.hpp"
#include "unite.hpp"
#include "fantassin.hpp"
#include "archer.hpp"
#include "catapulte.hpp"
#include "superSoldat.hpp"

class AireDeJeu {
	Unite* plateau[12];
	int tourDeJeu; // 1 (tour du joueur A) ou -1 (tour du joueur B)
	int nbToursActuel;
	int nbToursMAX;
	Joueur jA;
	Joueur jB;
	
	public:
		AireDeJeu();
		~AireDeJeu();

		// Méthodes et fonctions de récupération/affichage de valeur des attributs
		int getTourDeJeu() const {return tourDeJeu;};
		bool getMode() const {return jB.getMode();};
		void afficherInfos() const; // Affichage des informations principales
		friend std::ostream &operator<<(std::ostream &flux, const AireDeJeu &a); // Affichage de l'aire de jeu

		// Méthodes de modification de valeur des attributs
		void setAireDeJeu(int tourDeJeu0, int nbToursActuel0, int nbToursMAX0){tourDeJeu = tourDeJeu0; nbToursActuel = nbToursActuel0; nbToursMAX = nbToursMAX0;};
		void incrNbTourActuel() {nbToursActuel+=1;};
		void setNbToursMax(int val) {nbToursMAX = val;};
		void setMode(bool mode) {jB.setMode(mode);};
		void addArgent(int val) {jA.addArgent(val); jB.addArgent(val);};
		void reset();
		
		// Méthodes liées à l'enregistrement et au chargement de la partie
		bool charger(std::string entree);
		bool sauvegarder(std::string sortie) const;

		// Méthodes principales pour le déroulement de la partie
		void jouerActions();
		bool finTour(); // retourne true si le joueur fini son tour ; renvoie true s'il quitte la partie
		
		// Méthodes pour détecter la fin de partie
		bool tourMaxAtteint() const;
		bool baseDetruite() const;		
};

#endif
