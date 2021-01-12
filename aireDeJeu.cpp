#include <iostream>
#include "aireDeJeu.hpp"

AireDeJeu::~AireDeJeu() {}

void aireDeJeu::print() const {
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "AIRE DE JEU :" << std::endl;
	// affichage de l'aire de jeu avec les unités, bases des joueurs, points de vie restants pour chaque unité
	std::cout << "Tour " << nbToursActuel << "/" << nbToursMAX << endl; // non demandé par le sujet mais utile pour vérifier que nbToursActuel s'incrémente
	std::cout << "Pièces d'or du Joueur 1 : " << j1->getArgent() << std::endl;
	std::cout << "Pièces d'or du Joueur 2 : " << j2->getArgent() << std::endl;
}
