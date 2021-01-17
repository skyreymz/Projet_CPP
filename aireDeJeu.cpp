#include <iostream>
#include <fstream>
#include "aireDeJeu.hpp"
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
#include "fantassin.hpp"
#include "archer.hpp"
#include "catapulte.hpp"

AireDeJeu::AireDeJeu(bool mod, int tourActuel, int tourMaximum) {
	for (int i=0; i <= 12; i++) {
		plateau[i] = nullptr;
	}

	tourDeJeu = 1;
	nbToursActuel = tourActuel; // on laisse ça car plus tard on fera sans doute le chargement de partie -> nbToursActuel sera différent
	nbToursMAX = tourMaximum;
	jA = Joueur(0, 50);
	jB = Joueur(mod, 50);
}

AireDeJeu::~AireDeJeu() {}

bool AireDeJeu::charger(char* entree) {
	std::ifstream file(entree);
	if (!file) {
		std::cerr << "Ouverture de fichier impossible";
		return false;
	}
	try {
		std::string var;
		// Récupération des informations de la classe AireDeJeu
		std::getline(file, var);
		int tourDeJeu0 = std::stoi(var); // 1 ou -1, permet de differencier le joueur de gauche de celui de droite
		if ((tourDeJeu0 != 1) && (tourDeJeu0 !=-1)){
			throw 0;
		}

		std::getline(file, var);
		int nbToursActuel0 = std::stoi(var);
		if (nbToursActuel0 < 0) throw 0;

		std::getline(file, var);
		int nbToursMAX0 = std::stoi(var);
		if (nbToursMAX0 < nbToursActuel0) throw 0;


		// Récupération des informations des classes Joueur
		std::getline(file, var);
		int var2 = std::stoi(var);
		bool modeJB;
		if (var2 != 0 && var2 != 1) {
			throw 0;// 0 signifie manuel, 1 signifie automatique
		} else {
			modeJB = (var2 == 1);
		}

		std::getline(file, var);
		int argentJA = std::stoi(var);
		if (argentJA < 0) throw 0;// 0 signifie manuel, 1 signifie automatique

		std::getline(file, var);
		int argentJB = std::stoi(var);
		if (argentJB < 0) throw 0;// 0 signifie manuel, 1 signifie automatique

		std::getline(file, var);
		int pvBaseJA = std::stoi(var);

		std::getline(file, var);
		int pvBaseJB = std::stoi(var);


		// Récupération des informations des classes Unité
			/* Structure de ces données :
				   CAMP (A si on passe aux unités de l'équipe adverse)
			       TYPE DE L'UNITE (f fantassin ; a archer ; c catapulte ; s superSoldat ; N pas d'unité)
			       PV DE L'UNITE (s'il y a une unité)
			   Si le type est un espace, cela signifie qu'il n'y a pas d'unité sur cette position
			*/
		int camp = 1;
		char type;
		int pv;
		int position = 0;
		while (position < 12) {
			std::getline(file, var);
			type = var[0];
			if ((type != 'N') && (type != 'A') && (((position == 0) && (camp == -1)) || ((position == 11) && (camp == 1)))) {
				std::cerr << "Il ne peut pas y avoir d'unite d'une equipe au niveau de la position de la base adverse" << std::endl;
				throw 0;
			} 
			switch (type) {
				case 'A':
					if (camp == 1) {
						camp = -1;
					} else {
						throw 0;
					}
					break;
				case 'N':
					plateauCopie[position] = nullptr;
					position ++;
					//std::cout << "pas d'unité\n";
					break;
				case 'f':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Fantassin(pv, camp);
					position ++;
					//std::cout << "fantassin\n";
					break;
				case 'a':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Archer(pv, camp);
					position ++;
					//std::cout << "archer\n";
					break;
				case 'c':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Catapulte(pv, camp);
					position ++;
					//std::cout << "catapulte\n";
					break;
				case 's':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new SuperSoldat(pv, camp);
					position ++;
					//std::cout << "super soldat\n";
					break;
				default:
					throw 0;
			}
		}
		std::getline(file,var); // le dernier retour à la ligne
		if (!file.eof()) throw 1;

		// Les données sont valides, mise à jour de l'aire de jeu
		setAireDeJeu(tourDeJeu0, nbToursActuel0, nbToursMAX0);
		jA.setJoueur(     0, argentJA, pvBaseJA);
		jB.setJoueur(modeJB, argentJB, pvBaseJB);
		for (int i = 0 ; i < 12 ; i++) {
			plateau[i] = plateauCopie[i];
		}

		std::cout << "Chargement réussi !" << std::endl;
		return true;
		
	} catch (...) {
		std::cerr << "Echec lors de la récupération des données (Fichier invalide)" << std::endl;
		return false;
	}	
}

bool AireDeJeu::sauvegarder(char* sortie) const {
	std::ofstream file(sortie);
	if (!file) {
		std::cerr << "Ouverture de fichier impossible" << std::endl;
		return false;
	}

	try {
		// Stockage des informations de la classe AireDeJeu
		file << tourDeJeu << " // tourDeJeu : 1 ou -1, permet de differencier le joueur de gauche de celui de droite\n";
		file << nbToursActuel << " // nbTourActuel\n";
		file << nbToursMAX << " // nbTourMax\n";

		// Stockage des informations des classes Joueur
		file << jB.getMode() << " // mode du joueur B : 0 manuel ; 1 automatique\n";
		file << jA.getArgent() << " // argent joueur A\n";
		file << jB.getArgent() << " // argent joueur B\n";
		file << jA.getPvBase() << " // pv base joueur A\n";
		file << jB.getPvBase() << " // pv base joueur B\n";

		// Stockage des informations des classes Unité
		int campsUnites = 1; // camps de l'unité ajoutée
		for (int i = 0 ; i < 12 ; i++) {
			if (plateau[i] == nullptr) {
				file << "N // Position " << i << " : Sans unité\n";
			} else {
				std::string infosUnite = plateau[i]->getInfos();
				char campsUnite = infosUnite[2];
				if ((campsUnites == 1) && (campsUnite == 'B')) {
					campsUnites = -1;
					file << "A // Début des unités du joueur B\n";
				}
				switch (infosUnite[0]) { // pour connaître la classe de l'unité
					case 'F':
						file << "f // Position " << i << " : Fantassin\n";
						break;
					case 'A':
						file << "a // Position " << i << " : Archer\n";
						break;
					case 'C':
						file << "c // Position " << i << " : Catapulte\n";
						break;
					case 'S':
						file << "s // Position " << i << " : SuperSoldat\n";
						break;
					default:
						std::cerr << "Erreur dans la lecture des unités" << std::endl;
						throw 0;
				}
				file << plateau[i]->getPV() << " // Ses PV\n";
			}
		}

		std::cout << "Sauvegarde réussie !" << std::endl;
		return true;
	} catch (...) {
		std::cerr << "Echec lors de la sauvegarde des données (Fichier invalide)" << std::endl;
		return false;
	}
}

void AireDeJeu::print() const {
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "Tour " << nbToursActuel << "/" << nbToursMAX << std::endl; // non demandé par le sujet mais utile pour vérifier que nbToursActuel s'incrémente
	std::cout << "Pièces d'or du Joueur A : " << jA.getArgent() << std::endl;
	std::cout << "Pièces d'or du Joueur B : " << jB.getArgent() << std::endl;
	
	std::cout << "\nAIRE DE JEU :" << std::endl;
	std::cout << "Base A : " << jA.getPvBase() << "PV				  Base B : " << jB.getPvBase() << "PV" << std::endl;
	for (int i = 0 ; i < 51 ; i++){
		if (i == 0 || i == 50) {
			std::cout << "/\\/\\/\\";
		} else {
			 std::cout << "_";
		}
	}

	std::cout << "\n|";	

	for (int i = 0 ; i < 12 ; i++){
		if (plateau[i] != nullptr) {
			std::cout << plateau[i]->getInfos() << "|";
		} else {
			std::cout << "    |";
		}
	}

	std::cout << " <- Unité(camp)\n|";

	for (int i = 0 ; i < 12 ; i++){
		if (plateau[i] != nullptr) {
			int pv = plateau[i]->getPV();
			if (pv/10 == 0) {
				std::cout << "__" << pv << "_|";
			} else {
				std::cout << "_" << pv << "_|";
			}
		} else {
			std::cout << "____|";
		} 
	}
	std::cout << " <- PV des unités\n";	
}

bool AireDeJeu::finDeJeu() const {
	if (nbToursActuel >= nbToursMAX) {
		std::cout << "FIN DE JEU ! AUCUN VAINQUEUR !" << std::endl;
		return true;
	}

	if (jA.getPvBase() <= 0) {
		std::cout << "FIN DE JEU ! JOUEUR B VAINQUEUR !" << std::endl;
		return true;
	} else if (jB.getPvBase() <= 0) {
		std::cout << "FIN DE JEU ! JOUEUR A VAINQUEUR !" << std::endl;
		return true;
	}
	return false;
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

	char res;
	while (res != '0') {
		std::cout << "Voulez-vous créer une nouvelle unité ? (Entrez 'h' pour obtenir de l'aide) : ";
		std::cin >> res;
		switch (res) {
			case 'h':
				std::cout << "Si vous ne souhaitez pas créer d'unité, entrez '0'" << std::endl;
				std::cout << "Sinon, entrez le code d'une unité :" << std::endl;
				std::cout << "	Nom : Fantassin ; Prix : 10 pièces d'or ; Code : '1'" << std::endl;
				std::cout << "	Nom : Archer    ; Prix : 12 pièces d'or ; Code : '2'" << std::endl;
				std::cout << "	Nom : Catapulte ; Prix : 20 pièces d'or ; Code : '3'" << std::endl;	
				res = '0';
				break;
			case '0':
				break;
			case '1':
				if (j->getArgent() >= 10) {
					// création fantassin
					j->setArgent(-10);
					res = '0';
				} else {
					std::cout << "Vous n'avez pas assez d'argent" << std::endl; //sera inutile par la suite car on ne propose pas au joueur d'acheter une unité s'il a moins de 10PO
				}
				break;
			case '2':
				if (j->getArgent() >= 12) {
					// création archer
					j->setArgent(-12);
					res = '0';
				} else {
					std::cout << "Vous n'avez pas assez d'argent" << std::endl;
				}
				break;
			case '3':
				if (j->getArgent() >= 20) {
					// création catapulte
					j->setArgent(-20);
					res = '0';
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

	char choix;
	int indice;
	Joueur* joueur;
	bool equipe;
	int indiceUniteMAX; //utile pour l'action 2 et 3, potentiellement +/- 1 apres mouvement lors de l'action 2!

	// tourDeJeu == 1 signifie que c'est le tour du joueur A, donc jA
	// tourDeJeu == -1 signifie que c'est le tour du joueur B, donc jB

	// 1) Chaque joueur reçoit 8 pièces d'or (A SON TOUR ???????? Je vais considerer que oui...)
	if (tourDeJeu == 1) {
		jA.setArgent(8);
		indice = 0;
		joueur = &jA;
		equipe = false;
		indiceUniteMAX = -1; // s'il n'y a aucune unité de ce joueur sur le plateau
	} else {
		jB.setArgent(8);
		indice = 11;
		joueur = &jB;
		equipe = true;
		indiceUniteMAX = 12; // ou plus, tant que c'est strictement superieur à 11
	}


	// 2) Tour de jeu d'un joueur
	
	// Action 1
	
	for (int i=indice; ((tourDeJeu == 1) && (i < 11)) || ((tourDeJeu == -1) && (i > 0)); i=i+tourDeJeu) { 
		if (! (plateau[i] == nullptr)) {
			if (plateau[i]->getCamp() == tourDeJeu) {
				indiceUniteMAX = i;
				std::pair<bool,std::vector<int>> paire = plateau[i]->attaque(plateau, i);
				// On évolue le fantassin s'il a vaincu un fantassin ennemi
				if (paire.first) {
					int pv = plateau[i]->getPV();
					int camp = plateau[i]->getCamp(); //changer le camp et equipe en int 1 ou -1 !!!!! pck la c un bool
					delete plateau[i];
					plateau[i] = new SuperSoldat(pv, camp);
				}
				// On enlève les unités vaincus et ajoute les gains au joueur
				for (size_t j=0; j<paire.second.size(); j++) {
					joueur->setArgent(plateau[paire.second[j]]->getPrixDeces());
					delete plateau[paire.second[j]];
					plateau[paire.second[j]] = nullptr; // utile ? à tester
				}
			}
			else {
				break;
			}
		}
	}
	


	// Action 2
	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -=tourDeJeu ) {
		// to do
	}


	// Action 3

	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -=tourDeJeu ) {
		if (! (plateau[i] == nullptr)) {
			//if (plateau[i]->getCamp() == tourDeJeu) {
			if (plateau[i]->getAutreAction()) {
				std::pair<bool,std::vector<int>> paire = plateau[i]->attaque(plateau, i);
				// On évolue le fantassin s'il a vaincu un fantassin ennemi
				if (paire.first) {
					int pv = plateau[i]->getPV();
					int camp = plateau[i]->getCamp(); //changer le camp et equipe en int 1 ou -1 !!!!! pck la c un bool
					delete plateau[i];
					plateau[i] = new SuperSoldat(pv, camp);
				}
				// On enlève les unités vaincus et ajoute les gains au joueur
				for (size_t j=0; j<paire.second.size(); j++) {
					joueur->setArgent(plateau[paire.second[j]]->getPrixDeces());
					delete plateau[paire.second[j]];
					plateau[paire.second[j]] = nullptr; // utile ? à tester
				}
			}
			//}
			//else {
			//	break;
			//}
		}
	}




	// 3) Fin de tour d'un joueur
	if (plateau[indice] == nullptr) {
		if (!joueur->getMode()) { // Joueur en mode Manuel
			std::cout << "Phase de recrutement" << std::endl << "Vous pouvez recruter une des unités suivantes : ";
			std::cout << "Fantassin | Archer | Catapulte" << std::endl << "Votre choix ? (f | a | c | o pour ne pas recruter)" << std::endl;

			do { std::cin >> choix; } while ( (choix != 'f') && (choix != 'a') && (choix != 'c') && (choix != 'o') );

			if (joueur->getArgent() < 10) {
				while (choix != 'o') {
					std::cout << "Vous n'avez pas assez d'argent pour recruter" << std::endl << "Veuillez finir votre tour (en cliquant sur o)" << std::endl;
					std::cin >> choix;
				}
			}
			else if ( (joueur->getArgent() >= 10) && (joueur->getArgent() < 12) ) {
				while ((choix != 'o') && (choix != 'f')) {
					std::cout << "Vous ne pouvez recruter qu'un fantassin" << std::endl << "Veuillez recommencer" << std::endl;;
					std::cin >> choix;
				}
			}
			else if ( (joueur->getArgent() >= 12) && (joueur->getArgent() < 20) ) {
				while ((choix != 'o') && (choix != 'f') && (choix != 'a')) {
					std::cout << "Vous ne pouvez recruter qu'un fantassin ou qu'un archer" << std::endl << "Veuillez recommencer" << std::endl;;
					std::cin >> choix;
				}
			}
			else {

			}
			
			
			if (choix == 'f') {
				joueur->setArgent( (-1) * Fantassin::getPrix() );
				plateau[indice] = new Fantassin(equipe);
			}
			else if (choix == 'a') {
				joueur->setArgent( (-1) * Archer::getPrix() );
				plateau[indice] = new Archer(equipe);
			}
			else if (choix == 'c') {
				joueur->setArgent( (-1) * Catapulte::getPrix() );
				plateau[indice] = new Catapulte(equipe);
			}
			else {

			}
		} else { // Joueur en mode Automatique
			// Stratégie : création de l'unité la plus chère
			if (joueur->getArgent() >= 20) {
				joueur->setArgent( (-1) * Catapulte::getPrix() );
				plateau[indice] = new Catapulte(equipe);
			} else if (joueur->getArgent() >= 12) {
				joueur->setArgent( (-1) * Archer::getPrix() );
				plateau[indice] = new Archer(equipe);
			} else if (joueur->getArgent() >= 10) {
				joueur->setArgent( (-1) * Fantassin::getPrix() );
				plateau[indice] = new Fantassin(equipe);
			} else {}
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
