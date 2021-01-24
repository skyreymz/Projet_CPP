#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include "aireDeJeu.hpp"

AireDeJeu::AireDeJeu() {
	for (size_t i=0; i < 12; i++) {
		plateau[i] = nullptr;
	}

	tourDeJeu = 1;
	nbToursActuel = 1;
	jA = Joueur();
	jB = Joueur();
}

AireDeJeu::~AireDeJeu() {
	for (size_t i=0; i<12; i++) {
		delete plateau[i];
	}
}

void AireDeJeu::afficherTour() const {
	char tourJoueur;
	if (tourDeJeu == 1) {
		std::cout << "\n==============================================================\n";
		tourJoueur = 'A';
	} else {
		std::cout << "\n--------------------------------------------------------------\n";
		tourJoueur = 'B';
	}

	std::cout << "\nTOUR " << nbToursActuel << '/' << nbToursMAX << " - " << "Tour du joueur " << tourJoueur << std::endl;
}

std::ostream& operator<<(std::ostream &flux, AireDeJeu const &a) {
	flux << "\nPièces d'or du Joueur A : " << a.jA.getArgent() << std::endl;
	flux << "Pièces d'or du Joueur B : " << a.jB.getArgent() << std::endl;

	flux << "\nAIRE DE JEU :\n";
	flux << "Base A : " << std::setfill('0') << std::setw(3) << a.jA.getPvBase() << "PV";
	flux << "                                 Base B : " << std::setfill('0') << std::setw(3) << a.jB.getPvBase() << "PV" << std::endl;
	for (int i = 0 ; i < 51 ; i++){
		if (i == 0 || i == 50) {
			flux << "/\\/\\/\\";
		} else {
			 flux << "_";
		}
	}

	flux << "\n|";	

	for (int i = 0 ; i < 12 ; i++){
		if (a.plateau[i] != nullptr) {
			flux << *(a.plateau[i]) << '|';
		} else {
			flux << "    |";
		}
	}

	flux << " <- Unité(Camp)\n|";

	for (int i = 0 ; i < 12 ; i++){
		if (a.plateau[i] != nullptr) {
			int pv = a.plateau[i]->getPV();
			if (pv/10 == 0) {
				flux << "__" << pv << "_|";
			} else {
				flux << "_" << pv << "_|";
			}
		} else {
			flux << "____|";
		} 
	}
	
	flux << " <- Points de vie des unités\n ";	

	for (int i = 0 ; i < 12 ; i++){
		if (i/10 == 0) {
			flux << "  " << i << "  ";
		} else {
			flux << " " << i << "  ";
		}
	}
	flux << " <- Position\n";

	return flux;	
}

void AireDeJeu::reset() {
	for (size_t i=0; i < 12; i++) {
		delete plateau[i];
		plateau[i] = nullptr;
	}

	tourDeJeu = 1;
	nbToursActuel = 1;
	jA = Joueur();
	jB = Joueur();
}

bool AireDeJeu::charger(std::string entree) {
	std::ifstream file(entree);
	if (!file) {
		std::cerr << "Ouverture de fichier impossible" << std::endl;
		return false;
	}
	try {
		std::string var;

		// Récupération des informations principales de la classe AireDeJeu
		std::getline(file, var);
		int tourDeJeu0 = std::stoi(var); // 1 (tour du joueur A) ou -1 (tour du joueur B)
		if ((tourDeJeu0 != 1) && (tourDeJeu0 !=-1)){
			throw std::invalid_argument("tourDeJeu doit être égal à 1 (tour du joueur A) ou -1 (tour du joueur B)");
		}

		std::getline(file, var);
		int nbToursActuel0 = std::stoi(var);
		if (nbToursActuel0 <= 0) throw std::invalid_argument("nbToursActuel doit être strictement positif");

		std::getline(file, var);
		int nbToursMAX0 = std::stoi(var);
		if (nbToursMAX0 < nbToursActuel0) throw std::invalid_argument("nbToursMax doit être supérieur à nbToursActuel");


		// Récupération des informations des classes Joueur
		std::getline(file, var);
		int modeJBInt = std::stoi(var);
		bool modeJB;
		if (modeJBInt != 0 && modeJBInt != 1) {
			throw std::invalid_argument("Le mode du joueur B doit valoir 0 ou 1");// 0 (manuel) ou 1 (automatique)
		} else {
			modeJB = (modeJBInt == 1);
		}

		std::getline(file, var);
		int argentJA = std::stoi(var);
		if (argentJA < 0) throw std::invalid_argument("L'argent du joueur A doit être positif");

		std::getline(file, var);
		int argentJB = std::stoi(var);
		if (argentJB < 0) throw std::invalid_argument("L'argent du joueur B doit être positif");

		std::getline(file, var);
		int pvBaseJA = std::stoi(var);
		if (pvBaseJA < 0) throw std::invalid_argument("Les points de vie de la base du joueur A doivent être positifs");

		std::getline(file, var);
		int pvBaseJB = std::stoi(var);
		if (pvBaseJB < 0) throw std::invalid_argument("Les points de vie de la base du joueur B doivent être positifs");

		// Récupération des informations des classes Unité
			/* Structure de ces données pour chaque position :
			      "$ X" (facultatif) : Marque le début des unités du joueur B
				  TYPE DE L'UNITE ' ' PV DE L'UNITE (si et seulement s'il y a une unité)
               
               Les types possibles : 'f' pour Fantassin ; 'a' pour Archer ; 'c' pour Catapulte ; 's' pour SuperSoldat ; 'N' s'il n'y a pas d'Unité
			*/
		Unite* plateauCopie[12];
		int camp = 1;
		char type;
		int pv;
		int position = 0;
		while (position < 12) {
			std::getline(file, var, ' ');
			if (var.length() != 1) {
				throw std::invalid_argument("Type d'unité inconnu");
			}
			type = var[0];
			if ((type != 'N') && (type != '$') && (((position == 0) && (camp == -1)) || ((position == 11) && (camp == 1)))) {
				throw std::invalid_argument("Une unite d'une equipe ne peut occuper la base adverse");
			} 
			switch (type) {
				case '$':
					if (camp == 1) {
						camp = -1;
					} else {
						throw std::invalid_argument("\"$\" ne peut apparaître qu'une fois dans le fichier de sauvegarde");
					}
					std::getline(file, var); // retour à la ligne
					break;
				case 'N':
					plateauCopie[position] = nullptr;
					std::getline(file, var); // retour à la ligne
					position++;
					break;
				case 'f':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Fantassin(camp, pv);
					position++;
					break;
				case 'a':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Archer(camp, pv);
					position++;
					break;
				case 'c':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new Catapulte(camp, pv);
					position++;
					break;
				case 's':
					std::getline(file, var);
					pv = std::stoi(var);
					plateauCopie[position] = new SuperSoldat(camp, pv);
					position++;
					break;
				default:
					throw std::invalid_argument("Type d'unité inconnu");
			}
		}
		// Sécurités supplémentaires :
		std::getline(file,var); // le dernier retour à la ligne
		if (!file.eof()) throw std::invalid_argument("Le fichier de sauvegarde comporte plus de données que celles nécessaires");

		// Les données sont valides, mise à jour de l'aire de jeu
		setAireDeJeu(tourDeJeu0, nbToursActuel0, nbToursMAX0);
		jA.setJoueur(     0, argentJA, pvBaseJA);
		jB.setJoueur(modeJB, argentJB, pvBaseJB);
		for (int i = 0 ; i < 12 ; i++) {
			plateau[i] = plateauCopie[i];
		}
		
		file.close();
		std::cout << "\nLa partie a été correctement chargée !" << std::endl;
		return true;

	} catch (std::invalid_argument &e) {
		std::cerr << "Echec lors de la récupération des données : Argument invalide : " << e.what() << std::endl;
		file.close();
		return false;
	} catch (...) {
		std::cerr << "Echec lors de la récupération des données" << std::endl;
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
		// Stockage des informations principales de la classe AireDeJeu
		file << tourDeJeu << " // tourDeJeu : 1 (tour du joueur A) ou -1 (tour du joueur B)\n";
		file << nbToursActuel << " // nbToursActuel\n";
		file << nbToursMAX << " // nbToursMax\n";

		// Stockage des informations des classes Joueur
		file << jB.getMode() << " // Mode du joueur B : 0 (manuel) ou 1 (automatique)\n";
		file << jA.getArgent() << " // Argent joueur A\n";
		file << jB.getArgent() << " // Argent joueur B\n";
		file << jA.getPvBase() << " // Points de vie de la base du joueur A\n";
		file << jB.getPvBase() << " // Points de vie de la base du joueur B\n";

		// Stockage des informations des classes Unité
		int campsUnites = 1; // camps de l'unité ajoutée
		for (int i = 0 ; i < 12 ; i++) {
			if (plateau[i] == nullptr) {
				file << "N X // Position " << i << " : Sans unité\n";
			} else {
				if ((campsUnites == 1) && (plateau[i]->getCamp() == -1)) {
					campsUnites = -1;
					file << "$ X // Début des unités du joueur B\n";
				}
				switch (plateau[i]->getNomUnite()) { // pour connaître la classe de l'unité
					case 'F':
						file << "f " << plateau[i]->getPV() << " // Position " << i << " : Fantassin | " << plateau[i]->getPV() << "PV | Camp " << plateau[i]->getCampChar() << std::endl;
						break;
					case 'A':
						file << "a " << plateau[i]->getPV() << " // Position " << i << " : Archer | " << plateau[i]->getPV() << "PV | Camp " << plateau[i]->getCampChar() << std::endl;
						break;
					case 'C':
						file << "c " << plateau[i]->getPV() << " // Position " << i << " : Catapulte | " << plateau[i]->getPV() << "PV | Camp " << plateau[i]->getCampChar() << std::endl;
						break;
					case 'S':
						file << "s " << plateau[i]->getPV() << " // Position " << i << " : Super-soldat | " << plateau[i]->getPV() << "PV | Camp " << plateau[i]->getCampChar() << std::endl;
						break;
					default:
						throw std::invalid_argument("Type d'unité inconnu");
				}
			}
		}

		std::cout << "La partie a été correctement sauvegardée" << std::endl;
		file.close();
		return true;
	} catch (std::invalid_argument &e) {
		std::cerr << "Echec lors de la sauvegarde des données : " << e.what() << std::endl;
		file.close();
		return false;
	} catch (...) {
		std::cerr << "Echec lors de la sauvegarde des données"<< std::endl;
		file.close();
		return false;
	}
}

void AireDeJeu::jouerActions() {
	int indiceBase;
	Joueur* joueur;
	char campJoueur;
	int indiceUniteMAX; // utile pour les actions 2 et 3, potentiellement +/- 1 apres mouvement lors de l'action 2!
	Joueur* joueurAdverse;

	// tourDeJeu == 1 signifie tour du joueur A (jA)
	// tourDeJeu == -1 signifie tour du joueur B (jB)

	if (tourDeJeu == 1) {
		indiceBase = 0;
		joueur = &jA;
		campJoueur = 'A';
		indiceUniteMAX = -1; // S'il n'y a aucune unité de ce joueur sur le plateau (utile pour les boucles des actions 2 et 3)
		joueurAdverse = &jB;
	} else {
		indiceBase = 11;
		joueur = &jB;
		campJoueur = 'B';
		indiceUniteMAX = 12; // S'il n'y a aucune unité de ce joueur sur le plateau (utile pour les boucles des actions 2 et 3)
		joueurAdverse = &jA;
	}

	std::cout << "\nAffichage des actions des unités :" << std::endl;

	// Action 1	: Attaquer pour chacune des unités du joueur
	for (int i=indiceBase; ((tourDeJeu == 1) && (i < 11)) || ((tourDeJeu == -1) && (i > 0)); i += tourDeJeu) { 
		if (plateau[i] != nullptr) {
			if (plateau[i]->getCamp() == tourDeJeu) {
				indiceUniteMAX = i;
				std::vector<int> vaincus = plateau[i]->attaque(plateau, i, joueurAdverse);
				
				// On enlève les unités vaincues et ajoute les gains au joueur
				for (size_t j=0; j<vaincus.size(); j++) {
					if ( (plateau[vaincus[j]]->getCamp()) != tourDeJeu ) {
						std::cout << "Le joueur " << campJoueur << " a gagné " << plateau[vaincus[j]]->getPrixDeces() << " pièces d'or (décès de " << *(plateau[vaincus[j]]) << ")\n";
						joueur->addArgent(plateau[vaincus[j]]->getPrixDeces());
					}
					delete plateau[vaincus[j]];
					plateau[vaincus[j]] = nullptr;
				}
			}
			else {
				break;
			}
		}
	}

	// Action 2 : Avancer pour chacune des unités du joueur sauf Catapulte
	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -= tourDeJeu) {
		if (plateau[i] != nullptr) {
			if ((i + tourDeJeu) == (indiceBase + tourDeJeu * 11)) { // Si la case devant l'unité est la position de la base ennemie
				continue;
			}
			if (plateau[i]->getNomUnite() != 'C') {
				if (plateau[i + tourDeJeu] == nullptr) {
					plateau[i]->deplace(plateau, i);
					if (i == indiceUniteMAX) {
						indiceUniteMAX += tourDeJeu;
					}
				}
			}
		}
	}

	// Action 3
	for (int i = indiceUniteMAX ; ((tourDeJeu == 1) && (i>=0)) || ((tourDeJeu == -1) && (i <= 11)) ; i -= tourDeJeu) {
		if (plateau[i] != nullptr) {
			std::vector<int> vaincus;
			switch (plateau[i]->getNomUnite()) {
				case 'A':
					break;
				case 'F':
					if (!plateau[i]->getAutreAction()) {
						plateau[i]->setAutreAction(true);
						continue; // Permet de quitter le switch
					}
					[[fallthrough]];
				case 'S':
					vaincus = plateau[i]->attaque(plateau, i, joueurAdverse);
					// On enlève les unités vaincus et ajoute les gains au joueur
					for (size_t j=0; j<vaincus.size(); j++) {
						if ( (plateau[vaincus[j]]->getCamp()) != tourDeJeu ) {
							std::cout << "Le joueur " << campJoueur << " a gagné " << plateau[vaincus[j]]->getPrixDeces() << " pièces d'or (décès de " << *(plateau[vaincus[j]]) << ")\n";
							joueur->addArgent(plateau[vaincus[j]]->getPrixDeces());
						}
						delete plateau[vaincus[j]];
						plateau[vaincus[j]] = nullptr;
					}
					plateau[i]->setAutreAction(true);
					break;
				case 'C':
					if (plateau[i]->getAutreAction()) {
						if ((i + tourDeJeu) != (indiceBase + tourDeJeu * 11)) { // Si la case devant l'unité n'est pas celle de la base ennemie
							if (plateau[i + tourDeJeu] == nullptr) {									
								plateau[i]->deplace(plateau, i); // ne modifie pas la valeur de l'attribut autreAction
							}
						}
					} else {
						plateau[i]->setAutreAction(true);
					}
					break;
			}
		}
	}
}

bool AireDeJeu::finTour() { // Retourne true si le joueur fini son tour ; false s'il quitte la partie

	int indiceBase;
	Joueur* joueur;
	char campJoueur;

	// tourDeJeu == 1 signifie tour du joueur A (jA)
	// tourDeJeu == -1 signifie tour du joueur B (jB)

	if (tourDeJeu == 1) {
		indiceBase = 0;
		joueur = &jA;
		campJoueur = 'A';
	} else {
		indiceBase = 11;
		joueur = &jB;
		campJoueur = 'B';
	}

	// Fin de tour d'un joueur
	if (!joueur->getMode()) { // Joueur en mode Manuel

		std::string choixString;
		char choix;

		do {
			if ((plateau[indiceBase] == nullptr) && joueur->getArgent() >= 10) {
				std::cout << "Caractéristiques des unités ('h') / Recruter une unité ('f' / 'a' / 'c') / Ne rien faire ('o') / Sauvegarder ('s') / Quitter la partie en cours ('q') : ";
			} else {
				std::cout << "Caractéristiques des unités ('h') / Ne rien faire ('o') / Sauvegarder ('s') / Quitter la partie en cours ('q') : ";
			}

			std::cin >> choixString;
			if (choixString.length() != 1) {
				choix = '0';
			} else {
				choix = choixString.at(0);
			}
			
			switch (choix) {
				case 'h':
					std::cout << "\nFantassin    | Prix : 10 pièces d'or | Points de vie : 10 | Points d'attaque : 4 | Portée : 1" << std::endl;
					std::cout <<   "Archer       | Prix : 12 pièces d'or | Points de vie :  8 | Points d'attaque : 3 | Portée : 1, 2 ou 3" << std::endl;
					std::cout <<   "Catapulte    | Prix : 20 pièces d'or | Points de vie : 12 | Points d'attaque : 6 | Portée : 2 à 3 ou 3 à 4" << std::endl;
					std::cout <<   "Super-soldat | Prix :       --       | Points de vie : 10 | Points d'attaque : 4 | Portée : 1\n" << std::endl;
					choix = '0';
					break;
				case 'f':
					if (plateau[indiceBase] == nullptr) {
						if (joueur->getArgent() >= Fantassin::getPrix()) {
							joueur->addArgent( (-1) * Fantassin::getPrix() );
							plateau[indiceBase] = new Fantassin(tourDeJeu);
							std::cout << "\nLe joueur " << campJoueur << " a recruté un Fantassin" << std::endl;
							choix = '1';
						} else {
							std::cerr << "Vous n'avez pas assez d'argent pour recruter un Fantassin" << std::endl;
							choix = '0';
						}
					} else {
						std::cerr << "Une Unité occupe votre base" << std::endl;
							choix = '0';
					}
					break;
				case 'a':
					if (plateau[indiceBase] == nullptr) {
						if (joueur->getArgent() >= Archer::getPrix()) {
							joueur->addArgent( (-1) * Archer::getPrix() );
							plateau[indiceBase] = new Archer(tourDeJeu);
							std::cout << "\nLe joueur " << campJoueur << " a recruté un Archer" << std::endl;
							choix = '1';
						} else {
							std::cerr << "Vous n'avez pas assez d'argent pour recruter un Archer" << std::endl;
							choix = '0';
						}
					} else {
						std::cerr << "Une Unité occupe votre base" << std::endl;
						choix = '0';
					}
					break;
				case 'c':
					if (plateau[indiceBase] == nullptr) {
						if (joueur->getArgent() >= Catapulte::getPrix()) {
							joueur->addArgent( (-1) * Catapulte::getPrix() );
							plateau[indiceBase] = new Catapulte(tourDeJeu);
							std::cout << "\nLe joueur " << campJoueur << " a recruté une Catapulte" << std::endl;
							choix = '1';
						} else {
							std::cerr << "Vous n'avez pas assez d'argent pour recruter un Fantassin" << std::endl;
							choix = '0';
						}
					} else {
						std::cerr << "Une Unité occupe votre base" << std::endl;
						choix = '0';
					}
					break;
				case 'o':
					choix = '1';
					break;
				case 's':
					do {
						std::cout << "Entrez le nom du fichier où sauvegarder ('r' pour revenir à la partie en cours) : ";
						std::cin >> choixString;
						if (choixString == "r") {
							choix = '0';
						} else if(sauvegarder(choixString)) {
							choix = '0';
						} else {
							choix = '2';
						}
					} while (choix == '2');
					break;
				case 'q':
					std::cout << "\nFIN DE PARTIE ! ABANDON DU JOUEUR " << campJoueur << std::endl;
					std::cout << "\n==============================================================\n";
					return false;
				default :
					std::cerr << "Caractère(s) non reconnu(s)" << std::endl;
					choix = '0';
					break;
			}
		} while (choix == '0');
	} else {// Joueur en mode Automatique
		if (plateau[indiceBase] == nullptr) {
			// Stratégie : création de l'unité la plus chère
			if (joueur->getArgent() >= Catapulte::getPrix()) {
				joueur->addArgent( (-1) * Catapulte::getPrix() );
				std::cout << "\nLe joueur B a recruté une Catapulte" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
				plateau[indiceBase] = new Catapulte(tourDeJeu);
			} else if (joueur->getArgent() >= Archer::getPrix()) {
				joueur->addArgent( (-1) * Archer::getPrix() );
				std::cout << "\nLe joueur B a recruté un Archer" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
				plateau[indiceBase] = new Archer(tourDeJeu);
			} else if (joueur->getArgent() >= Fantassin::getPrix()) {
				joueur->addArgent( (-1) * Fantassin::getPrix() );
				std::cout << "\nLe joueur B a recruté un Fantassin" << std::endl; // il n'y a que le joueur B qui peut être en mode automatique
				plateau[indiceBase] = new Fantassin(tourDeJeu);
			} else {
				std::cout << "\nLe joueur B n'a pas assez de pièces d'or pour recruter" << std::endl;
			}
		}
	}
	tourDeJeu = -tourDeJeu;
	return true;
}

bool AireDeJeu::tourMaxAtteint() const {
	if ((tourDeJeu == 1) && (nbToursActuel == nbToursMAX)) {
		std::cout << "\nFIN DE PARTIE ! TOUR MAXIMUM DEPASSE ! ";
		if (jA.getPvBase() > jB.getPvBase()) {
			std::cout << "VICTOIRE DU JOUEUR A (les points de vie de sa Base sont strictements supérieurs) !" << std::endl;
		} else if (jA.getPvBase() < jB.getPvBase()) {
			std::cout << "VICTOIRE DU JOUEUR B (les points de vie de sa Base sont strictements supérieurs) !" << std::endl;
		} else {
			if (jA.getArgent() > jB.getArgent()) {
				std::cout << "VICTOIRE DU JOUEUR A (il a le plus de pièces d'or) !" << std::endl;
			} else if (jA.getArgent() < jB.getArgent()) {
				std::cout << "VICTOIRE DU JOUEUR B (il a le plus de pièces d'or) !" << std::endl;
			} else {
				std::cout << "AUCUN VAINQUEUR !" << std::endl;
			}
		}
		std::cout << "\n==============================================================\n";
		return true;
	}
	return false;
}

bool AireDeJeu::baseDetruite() const {
	if ((jA.getPvBase() <= 0)) {
		std::cout << "\nFIN DE PARTIE ! VICTOIRE DU JOUEUR B !" << std::endl;
		std::cout << "\n==============================================================\n";
		return true;
	} else if ((jB.getPvBase() <= 0)) {
		std::cout << "\nFIN DE PARTIE ! VICTOIRE DU JOUEUR A !" << std::endl;
		std::cout << "\n==============================================================\n";
		return true;
	}
	return false;
}