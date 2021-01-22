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

AireDeJeu::AireDeJeu() {
	for (int i=0; i <= 12; i++) {
		plateau[i] = nullptr;
	}

	tourDeJeu = 1;
	nbToursActuel = 0;
	jA = Joueur(0, 50);
	jB = Joueur(0, 50);
}

AireDeJeu::~AireDeJeu() {}

void AireDeJeu::resetAireDeJeu() {
	for (int i=0; i <= 12; i++) {
		plateau[i] = nullptr;
	}

	tourDeJeu = 1;
	nbToursActuel = 0;
	jA = Joueur(0, 50);
	jB = Joueur(0, 50);
}

bool AireDeJeu::charger(std::string entree) {
	std::ifstream file(entree);
	if (!file) {
		std::cerr << "Ouverture de fichier impossible" << std::endl;
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
		Unite* plateauCopie[12];
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
		file.close();
		return true;
		
	} catch (...) {
		std::cerr << "Echec lors de la récupération des données (Fichier invalide)" << std::endl;
		file.close();		
		return false;
	}	
}

bool AireDeJeu::sauvegarder(std::string sortie) const {
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
				if ((campsUnites == 1) && (plateau[i]->getCamp() == -1)) {
					campsUnites = -1;
					file << "A // Début des unités du joueur B\n";
				}
				switch (plateau[i]->getNomUnite()) { // pour connaître la classe de l'unité
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
		file.close();
		return true;
	} catch (...) {
		std::cerr << "Echec lors de la sauvegarde des données (Fichier invalide)" << std::endl;
		file.close();
		return false;
	}
}

void AireDeJeu::print() const {
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "Tour " << nbToursActuel << '/' << nbToursMAX << " ; Tour du joueur ";	
	if (tourDeJeu == 1) {
		std::cout << 'A' << std::endl;
	} else {
		std::cout << 'B' << std::endl;
	}	
	std::cout << "Pièces d'or du Joueur A : " << jA.getArgent() << std::endl;
	std::cout << "Pièces d'or du Joueur B : " << jB.getArgent() << std::endl;

	std::cout << "\nAIRE DE JEU :" << std::endl;
	std::cout << "Base A : " << jA.getPvBase() << "PV                                 Base B : " << jB.getPvBase() << "PV" << std::endl;
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
			char camps;
			if (plateau[i]->getCamp() == 1) {
				camps = 'A';
			} else {
				camps = 'B';
			}
			std::cout << plateau[i]->getNomUnite() << '(' << camps << ")|";
		} else {
			std::cout << "    |";
		}
	}

	std::cout << " <- Unité(Camp)\n|";

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
	
	std::cout << " <- PV des unités\n ";	

	for (int i = 0 ; i < 12 ; i++){
		if (i/10 == 0) {
			std::cout << "  " << i << "  ";
		} else {
			std::cout << " " << i << "  ";
		}
	}
	std::cout << " <- Position\n";	
}

bool AireDeJeu::tourMaxAtteint() const {
	if ((tourDeJeu == 1) && (nbToursActuel == nbToursMAX)) {
		std::cout << "FIN DE JEU ! Nombre de tours maximum dépassé ! AUCUN VAINQUEUR !" << std::endl;
		return true;
	}
	return false;
}

bool AireDeJeu::baseDetruite() const {
	if ((jA.getPvBase() <= 0)) {
		std::cout << "FIN DE JEU ! VICTOIRE DU JOUEUR B !" << std::endl;
		return true;
	} else if ((jB.getPvBase() <= 0)) {
		std::cout << "FIN DE JEU ! VICTOIRE DU JOUEUR A !" << std::endl;
		return true;
	}
	return false;
}


void AireDeJeu::jouerActions() {
	
	int indice;
	Joueur* joueur;
	int indiceUniteMAX; //utile pour l'action 2 et 3, potentiellement +/- 1 apres mouvement lors de l'action 2!
	Joueur* joueurAdverse;

	// tourDeJeu == 1 signifie que c'est le tour du joueur A, donc jA
	// tourDeJeu == -1 signifie que c'est le tour du joueur B, donc jB

	// 1) Chaque joueur reçoit 8 pièces d'or (L'énoncé implique que les deux joueurs gagnent l'argent au meme moment...)
	if (tourDeJeu == 1) {
		nbToursActuel++;
		jA.setArgent(8);
		jB.setArgent(8);
		indice = 0;
		joueur = &jA;
		joueurAdverse = &jB;
		indiceUniteMAX = -1; // s'il n'y a aucune unité de ce joueur sur le plateau
	} else {
		indice = 11;
		joueur = &jB;
		joueurAdverse = &jA;
		indiceUniteMAX = 12; // ou plus, tant que c'est strictement superieur à 11
	}


	// 2) Tour de jeu d'un joueur
	
	// Action 1	
	for (int i=indice; ((tourDeJeu == 1) && (i < 11)) || ((tourDeJeu == -1) && (i > 0)); i=i+tourDeJeu) { 
		if (plateau[i] != nullptr) {
			if (plateau[i]->getCamp() == tourDeJeu) {
				indiceUniteMAX = i;
				std::pair<bool,std::vector<int>> paire = plateau[i]->attaque(plateau, i, joueurAdverse);
				// On évolue le fantassin s'il a vaincu un fantassin ennemi
				if (paire.first) {
					int pv = plateau[i]->getPV();
					int camp = plateau[i]->getCamp(); //changer le camp et equipe en int 1 ou -1 !!!!! pck la c un bool
					delete plateau[i];
					plateau[i] = new SuperSoldat(pv, camp);
				}
				// On enlève les unités vaincus et ajoute les gains au joueur
				for (size_t j=0; j<paire.second.size(); j++) {
					if ( (plateau[paire.second[j]]->getCamp()) != tourDeJeu ) {
						joueur->setArgent(plateau[paire.second[j]]->getPrixDeces());
					}
					delete plateau[paire.second[j]];
					plateau[paire.second[j]] = nullptr;
				}
			}
			else {
				break;
			}
		}
	}
	


	// Action 2
	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -=tourDeJeu ) {
		if (plateau[i] != nullptr) {
			if ((i + tourDeJeu) == (indice + tourDeJeu * 11)) {
				continue;
			}
			if (plateau[i + tourDeJeu] == nullptr) {
				switch(plateau[i]->getNomUnite()) {
					case 'F':
						plateau[i + tourDeJeu] = new Fantassin(plateau[i]->getPV(), plateau[i]->getCamp());
						std::cout << "F(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé sur la case " << i+tourDeJeu << std::endl;
						delete plateau[i];
						plateau[i] = nullptr;
						break;
					case 'A':
						plateau[i + tourDeJeu] = new Archer(plateau[i]->getPV(), plateau[i]->getCamp());
						std::cout << "A(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé sur la case " << i+tourDeJeu << std::endl;
						delete plateau[i];
						plateau[i] = nullptr;
						break;
					case 'S':
						plateau[i + tourDeJeu] = new SuperSoldat(plateau[i]->getPV(), plateau[i]->getCamp());
						std::cout << "S(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé sur la case " << i+tourDeJeu << std::endl;
						delete plateau[i];
						plateau[i] = nullptr;
						break;
				}
				
				if (i == indiceUniteMAX) {
					indiceUniteMAX += tourDeJeu;
				}
			}
		}
	}


	// Action 3
	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -=tourDeJeu ) {
		if (plateau[i] != nullptr) {
			//if (plateau[i]->getCamp() == tourDeJeu) {
			if (plateau[i]->getAutreAction()) {
				std::pair<bool,std::vector<int>> paire;
				switch (plateau[i]->getNomUnite()) {
					case 'F':
						paire = plateau[i]->attaque(plateau, i, joueurAdverse);
						// On évolue le fantassin s'il a vaincu un fantassin ennemi
						if (paire.first) {
							int pv = plateau[i]->getPV();
							int camp = plateau[i]->getCamp(); //changer le camp et equipe en int 1 ou -1 !!!!! pck la c un bool
							delete plateau[i];
							plateau[i] = new SuperSoldat(pv, camp);
						}
						// On enlève les unités vaincus et ajoute les gains au joueur
						for (size_t j=0; j<paire.second.size(); j++) {
							if ( (plateau[paire.second[j]]->getCamp()) != tourDeJeu ) {
								joueur->setArgent(plateau[paire.second[j]]->getPrixDeces());
							}
							delete plateau[paire.second[j]];
							plateau[paire.second[j]] = nullptr;
						}
						break;
					case 'S':
						paire = plateau[i]->attaque(plateau, i, joueurAdverse);
						// On enlève les unités vaincus et ajoute les gains au joueur
						for (size_t j=0; j<paire.second.size(); j++) {
							if ( (plateau[paire.second[j]]->getCamp()) != tourDeJeu ) {
								joueur->setArgent(plateau[paire.second[j]]->getPrixDeces());
							}
							delete plateau[paire.second[j]];
							plateau[paire.second[j]] = nullptr;
						}
						break;
					case 'C':
						if (plateau[i + tourDeJeu] == nullptr) {
							plateau[i + tourDeJeu] = new Catapulte(plateau[i]->getPV(), plateau[i]->getCamp());
							std::cout << "C(" << plateau[i]->getCampChar() << ")(position " << i << ") a avancé sur la case " << i+tourDeJeu << std::endl;
							delete plateau[i];
							plateau[i] = nullptr;
							break;
						}
				}
			} else if ((plateau[i]->getNomUnite() == 'F') || (plateau[i]->getNomUnite() == 'C')) {
				plateau[i]->setAutreAction(true);
			}
		}
	}
}


void AireDeJeu::finTour() { // retourne false si le joueur quitte la partie ; true sinon

	char choix;
	int indice;
	Joueur* joueur;

	// tourDeJeu == 1 signifie que c'est le tour du joueur A, donc jA
	// tourDeJeu == -1 signifie que c'est le tour du joueur B, donc jB

	if (tourDeJeu == 1) {
		indice = 0;
		joueur = &jA;
	} else {
		indice = 11;
		joueur = &jB;
	}

	// 3) Fin de tour d'un joueur
	if (!joueur->getMode()) { // Joueur en mode Manuel
		do {
			do {
				std::cout << "Recruter une unité ('f' / 'a' / 'c') / Ne rien faire ('o') / Sauvegarder ('s') / Quitter la partie en cours ('q') : ";
				std::cin >> choix;
			} while ((choix != 'f') && (choix != 'a') && (choix != 'c') && (choix != 'o') && (choix != 's') && (choix != 'q'));
			std::string nomFichier; // nom du fichier pour la sauvegarde
			switch (choix) {
				case 'f':
					if (plateau[indice] == nullptr) {
						if (joueur->getArgent() >= Fantassin::getPrix()) {
							joueur->setArgent( (-1) * Fantassin::getPrix() );
							plateau[indice] = new Fantassin(tourDeJeu);
						} else {
							std::cout << "Erreur : Vous n'avez pas assez d'argent pour recruter un Fantassin" << std::endl;
							choix = '0';
						}
					} else {
						std::cout << "Erreur : Il y a déjà une Unité sur votre base" << std::endl;
							choix = '0';
					}
					break;
				case 'a':
					if (plateau[indice] == nullptr) {
						if (joueur->getArgent() >= Archer::getPrix()) {
							joueur->setArgent( (-1) * Archer::getPrix() );
							plateau[indice] = new Archer(tourDeJeu);
						} else {
							std::cout << "Erreur : Vous n'avez pas assez d'argent pour recruter un Fantassin" << std::endl;
							choix = '0';
						}
					} else {
						std::cout << "Erreur : Il y a déjà une Unité sur votre base" << std::endl;
						choix = '0';
					}
					break;
				case 'c':
					if (plateau[indice] == nullptr) {
						if (joueur->getArgent() >= Catapulte::getPrix()) {
							joueur->setArgent( (-1) * Catapulte::getPrix() );
							plateau[indice] = new Catapulte(tourDeJeu);
						} else {
							std::cout << "Erreur : Vous n'avez pas assez d'argent pour recruter un Fantassin" << std::endl;
							choix = '0';
						}
					} else {
						std::cout << "Erreur : Il y a déjà une Unité sur votre base" << std::endl;
						choix = '0';
					}
					break;
				case 'o':
					break;
				case 's':
					do {
						std::cout << "Entrez le nom du fichier à sauvegarder ('r' pour revenir à la partie en cours) :";
						std::cin >> nomFichier;
						if (nomFichier == "r") {
							choix = '0';
						} else if(this->sauvegarder(nomFichier)) {
							choix = '0';
						} else {
							choix = '1';
						}
					} while (choix == '1');
					break;
				case 'q':
					joueur->detruireBase(); // Abandon du joueur => pv de sa base mis à 0 => défaite du joueur
					break;
			}
		} while (choix == '0');
	} else {// Joueur en mode Automatique
		// Stratégie : création de l'unité la plus chère
		if (joueur->getArgent() >= 20) {
			joueur->setArgent( (-1) * Catapulte::getPrix() );
			std::cout << "Le joueur B a recruté une Catapulte" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
			plateau[indice] = new Catapulte(tourDeJeu);
		} else if (joueur->getArgent() >= 12) {
			joueur->setArgent( (-1) * Archer::getPrix() );
			std::cout << "Le joueur B a recruté un Archer" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
			plateau[indice] = new Archer(tourDeJeu);
		} else if (joueur->getArgent() >= 10) {
			joueur->setArgent( (-1) * Fantassin::getPrix() );
			std::cout << "Le joueur B a recruté un Fantassin" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
			plateau[indice] = new Fantassin(tourDeJeu);
		}

	}

	tourDeJeu = -tourDeJeu;
/*

	if (plateau[indice] == nullptr) {
		if (!joueur->getMode()) { // Joueur en mode Manuel
			//std::cout << "Phase de recrutement" << std::endl << "Vous pouvez recruter une des unités suivantes : ";
			//std::cout << "Fantassin | Archer | Catapulte" << std::endl << "Votre choix ? (f | a | c | o pour ne pas recruter)" << std::endl;

			//do { std::cin >> choix; } while ( (choix != 'f') && (choix != 'a') && (choix != 'c') && (choix != 'o') );

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
			}
		}

		

	}*/

}

/*std::ostream &operator<<(std::ostream &flux, const AireDeJeu *a) {
	//flux << " a ";
	flux << a->baseDetruite() << " aaaaaaaaaaaaaaa" << "bbbbbbbb";
	//flux << " b ";
	return flux;
}*/
