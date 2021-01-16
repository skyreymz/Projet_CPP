#include <iostream>
#include "aireDeJeu.hpp"
#include "fantassin.hpp"
#include "archer.hpp"
#include "catapulte.hpp"

AireDeJeu::AireDeJeu(bool mode, int tourMaximum = 100) {
	for (int i=0; i<=12; i++) {
		plateau[i] = nullptr;
	}
	tourDeJeu = 1;
	nbToursActuel = 0;
	nbToursMAX = tourMaximum;
	j1 = new Joueur(0, 50);
	j2 = new Joueur(mode, 50);
}

AireDeJeu::~AireDeJeu() {}

void AireDeJeu::print() const {
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "AIRE DE JEU :" << std::endl;
	// affichage de l'aire de jeu avec les unités, bases des joueurs, points de vie restants pour chaque unité
	std::cout << "Tour " << nbToursActuel << "/" << nbToursMAX << std::endl; // non demandé par le sujet mais utile pour vérifier que nbToursActuel s'incrémente
	std::cout << "Pièces d'or du Joueur 1 : " << j1->getArgent() << std::endl;
	std::cout << "Pièces d'or du Joueur 2 : " << j2->getArgent() << std::endl;
}

void AireDeJeu::jouerTour() {

	// tourDeJeu == 1 signifie que c'est le tour du joueur A, donc j1
	// tourDeJeu == -1 signifie que c'est le tour du joueur B, donc j2

	// 1) Chaque joueur reçoit 8 pièces d'or (A SON TOUR ???????? Je vais considerer que oui...)
	if (tourDeJeu == 1) {
		j1->setArgent(8);
	} else {
		j2->setArgent(8);
	}


	// 2) Tour de jeu du joueur A
	if (tourDeJeu == 1){

	}
	// 3) Tour de jeu du joueur B
	else {
		
	}


	// 4) Fin de tour d'un joueur
	char choix;
	int indice;

	if (tourDeJeu == 1) {
		indice = 0;
	} else {
		indice = 11;
	}

	if (plateau[indice] == nullptr) {

		std::cout << "Phase de recrutement" << std::endl << "Vous pouvez recruter une des unités suivantes : ";
		std::cout << "Fantassin | Archer | Catapulte" << std::endl << "Votre choix ? (f | a | c | o pour ne pas recruter)" << std::endl;

		do { std::cin >> choix; } while ( (choix != 'f') && (choix != 'a') && (choix != 'c') && (choix != 'o') );

		if (j1->getArgent() < 10) {
			while (choix != 'o') {
				std::cout << "Vous n'avez pas assez d'argent pour recruter" << std::endl << "Veuillez finir votre tour (en cliquant sur o)" << std::endl;
				std::cin >> choix;
			}
		}
		else if ( (j1->getArgent() >= 10) && (j1->getArgent() < 12) ) {
			while ((choix != 'o') && (choix != 'f')) {
				std::cout << "Vous ne pouvez recruter qu'un fantassin" << std::endl << "Veuillez recommencer" << std::endl;;
				std::cin >> choix;
			}
		}
		else if ( (j1->getArgent() >= 12) && (j1->getArgent() < 20) ) {
			while ((choix != 'o') && (choix != 'f') && (choix != 'a')) {
				std::cout << "Vous ne pouvez recruter qu'un fantassin ou qu'un archer" << std::endl << "Veuillez recommencer" << std::endl;;
				std::cin >> choix;
			}
		}
		else {

		}
		
		
		if (choix == 'f') {
			j1->setArgent( (-1) * Fantassin::getPrix() );
			plateau[indice] = new Fantassin();
		}
		else if (choix == 'a') {
			j1->setArgent( (-1) * Archer::getPrix() );
			plateau[indice] = new Archer();
		}
		else if (choix == 'c') {
			j1->setArgent( (-1) * Catapulte::getPrix() );
			plateau[indice] = new Catapulte();
		}
		else {

		}

	}


}



	/*


2. Tour de jeu du joueur A
(a) Phase de résolution des actions 1 des unités du joueur A
(b) Phase de résolution des actions 2 des unités du joueur A
(c) Phase de résolution des actions 3 des unités du joueur A
(d) Création éventuelle d'une nouvelle unité du joueur A
3. Tour de jeu du joueur B
(a) Phase de résolution des actions 1 des unités du joueur B
(b) Phase de résolution des actions 2 des unités du joueur B
3
(c) Phase de résolution des actions 3 des unités du joueur B
(d) Création éventuelle d'une nouvelle unité du joueur B


L'ordre dans lequel les unités eectuent leur action dépend de la phase :
• Lors de la phase de résolution des actions 1, l'unité la plus proche de la base du joueur
courant tente d'eectuer son action en premier, puis la deuxième unité la plus proche
et ainsi de suite jusqu'à l'unité la plus lointaine de la base du joueur.
• Lors des phases de résolution des actions 2 et 3, l'unité la plus lointaine de la base du
joueur courant tente d'eectuer son action en premier, puis la deuxième unité la plus
lointaine et ainsi de suite jusqu'à l'unité la plus proche de la base du joueur.

A chaque étape, si l'unité a la possibilité de faire son action, elle l'eectue obligatoirement.
A la n de son tour de jeu, le joueur a la possibilité de recruter une unité sur la case de sa base
s'il possède assez de pièces d'or (le coût de recrutement est alors retranché de ce qu'il possède)




	*/
