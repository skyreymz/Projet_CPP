#include <iostream>
#include "aireDeJeu.hpp"
#include <string>

AireDeJeu::AireDeJeu(bool mod, int tourActuel, int tourMaximum) {
	for (int i=0; i <= 12; i++) {
		plateau[i] = nullptr;
	}

	tourDeJeu = 0;
	nbToursActuel = tourActuel; // on laisse ça car plus tard on fera sans doute le chargement de partie -> nbToursActuel sera différent
	nbToursMAX = tourMaximum;
	mode = mod;
	jA = Joueur(0, 50);
	jB = Joueur(mod, 50);
}

AireDeJeu::~AireDeJeu() {}

void AireDeJeu::print() const {
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "Tour " << nbToursActuel << "/" << nbToursMAX << std::endl; // non demandé par le sujet mais utile pour vérifier que nbToursActuel s'incrémente
	std::cout << "Pièces d'or du Joueur A : " << jA.getArgent() << std::endl;
	std::cout << "Pièces d'or du Joueur B : " << jB.getArgent() << std::endl;
	
	std::cout << "\nAIRE DE JEU :" << std::endl;
	std::cout << "Base A : " << jA.getPvBase() << "PV				  Base B : " << jB.getPvBase() << "PV" << std::endl;
	for (int i = 0 ; i < 46 ; i++){
		if (i == 0 || i == 45) {
			std::cout << "/\\/\\/\\";
		} else {
			 std::cout << "_";
		}
	}

	std::cout << "\n|";	

	for (int i = 0 ; i < 11 ; i++){
		if (plateau[i] != nullptr) {
			std::cout << plateau[i]->getInfos() << "|";
		} else {
			std::cout << "    |";
		}
	}

	std::cout << " <- Unité(camp)\n|";

	for (int i = 0 ; i < 11 ; i++){
		if (plateau[i] != nullptr) {
			int pv = plateau[i]->getPV();
			if (pv/10 == 0) {
				std::cout << "  " << pv << "  |";
			} else {
				std::cout << " " << pv << " |";
			}
		} else {
			std::cout << "    |";
		} 
	}
	std::cout << " <- Points de vie des unités\n";

	for (int i = 0 ; i < 56 ; i++) std::cout << "_";
	std::cout << std::endl;	
}

void AireDeJeu::nouveauTour() {
	// il faut vérifier à la fin des actions 1 et 3 si une base est détruite (fin de jeu)
	// il faut vérifier si le nombre maximum de tour est atteint (fin de jeu)

	nbToursActuel++;
	jA.setArgent(8);
	jB.setArgent(8);

	// Tour du joueur A
		//Phase de résoution des actions 1 à 3 du joueur A

		// Création éventuelle d'une nouvelle unité :
		if (jA.getArgent() >= 10 /*&& (pas d'unité sur sa base) */){ // on propose que s'il a assez d'argent
			creationUniteManuelle(0);
		}

	// Tour du joueur B
		//Phase de résoution des actions 1 à 3 du joueur B

		if (jB.getArgent() >= 10 /*&& (pas d'unité sur sa base) */){ // on propose que s'il a assez d'argent
			creationUniteManuelle(1);
		}

	
}

void AireDeJeu::creationUniteManuelle(bool joueur){
	Joueur* j; // pointeur vers le joueur concerné
	if (!joueur) {
		j = &jA;
	} else {
		j = &jB;
	}

	int res = -1;
	while (res != 0) {
		std::cout << "Voulez-vous créer une nouvelle unité ? (Entrez -1 pour obtenir de l'aide) : ";
		//std::cin >> res; // TO DO
		res = 1;
		switch (res) {
			case -1:
				std::cout << "Si vous ne souhaitez pas créer d'unité, entrez 0" << std::endl;
				std::cout << "Sinon, entrez le code d'une unité :" << std::endl;
				std::cout << "	Nom : Fantassin ; Prix : 10 pièces d'or ; Code : 1" << std::endl;
				std::cout << "	Nom : Archer    ; Prix : 12 pièces d'or ; Code : 2" << std::endl;
				std::cout << "	Nom : Catapulte ; Prix : 20 pièces d'or ; Code : 3" << std::endl;	
				res = 0;
				break;
			case 0:
				break;
			case 1:
				//if (j->getArgent() >= 10) {
					// création fantassin
					j->setArgent(-10);
					res = 0;
				/*} else {
					std::cout << "Vous n'avez pas assez d'argent" << std::endl; //sera inutile par la suite car on ne propose pas au joueur d'acheter une unité s'il a moins de 10PO
				}*/
				break;
			case 2:
				if (j->getArgent() >= 12) {
					// création archer
					j->setArgent(-12);
					res = 0;
				} else {
					std::cout << "Vous n'avez pas assez d'argent" << std::endl;
				}
				break;
			case 3:
				if (j->getArgent() >= 20) {
					// création catapulte
					j->setArgent(-20);
					res = 0;
				} else {
					std::cout << "Vous n'avez pas assez d'argent" << std::endl;
				}
				break;
			default:
				std::cerr << "Vous devez saisir un chiffre entre 0 et 3" << std::endl;
		}
	}
}

void AireDeJeu::jouerTour() {

	// tourDeJeu == 1 signifie que c'est le tour du joueur A, donc jA
	// tourDeJeu == -1 signifie que c'est le tour du joueur B, donc jB

	// 1) Chaque joueur reçoit 8 pièces d'or (A SON TOUR ???????? Je vais considerer que oui...)
	if (tourDeJeu == 1) {
		jA.setArgent(8);
	} else {
		jB.setArgent(8);
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

		if (jA.getArgent() < 10) {
			while (choix != 'o') {
				std::cout << "Vous n'avez pas assez d'argent pour recruter" << std::endl << "Veuillez finir votre tour (en cliquant sur o)" << std::endl;
				std::cin >> choix;
			}
		}
		else if ( (jA.getArgent() >= 10) && (jA.getArgent() < 12) ) {
			while ((choix != 'o') && (choix != 'f')) {
				std::cout << "Vous ne pouvez recruter qu'un fantassin" << std::endl << "Veuillez recommencer" << std::endl;;
				std::cin >> choix;
			}
		}
		else if ( (jA.getArgent() >= 12) && (jA.getArgent() < 20) ) {
			while ((choix != 'o') && (choix != 'f') && (choix != 'a')) {
				std::cout << "Vous ne pouvez recruter qu'un fantassin ou qu'un archer" << std::endl << "Veuillez recommencer" << std::endl;;
				std::cin >> choix;
			}
		}
		else {

		}
		
		
		if (choix == 'f') {
			jA.setArgent( (-1) * Fantassin::getPrix() );
			plateau[indice] = new Fantassin(0);
		}
		else if (choix == 'a') {
			jA.setArgent( (-1) * Archer::getPrix() );
			plateau[indice] = new Archer(0);
		}
		else if (choix == 'c') {
			jA.setArgent( (-1) * Catapulte::getPrix() );
			plateau[indice] = new Catapulte(0);
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
