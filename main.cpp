#include "aireDeJeu.hpp"
#include <string>

int main() {
	std::cout << "\nProjet C++ : Age of War" << std::endl;

	//INSTANCIATION D'UNE AIRE DE JEU
	AireDeJeu* a = new AireDeJeu();

	bool finDePartie = false;
	char res;
	do {
		do {
			do {
				std::cout << "Commencer une Nouvelle partie ('n') / Charger une partie ('c') : ";
				std::cin >> res;
			} while ((res != 'n') && (res != 'c'));

			switch (res) {
				case 'n' :
					do {
						std::cout << "Joueur contre Joueur ('j') / Joueur contre IA ('m') : ";
						std::cin >> res;
					} while ((res != 'j') && (res != 'm'));
					if (res == 'j') {
						a->setMode(false);
						res = '1';
					} else {
						a->setMode(true);
						res = '1';
					}
					do {
						std::string nbTourMaxString;
						std::cout << "Entrez le nombre maximum de tours (au moins 1) : ";
						std::cin >> nbTourMaxString;
						try {
							int nbTourMaxInt = std::stoi(nbTourMaxString);
							if (nbTourMaxInt < 1) {
								res = '0';
							} else {
								a->setNbToursMax(nbTourMaxInt);
								res = '1';
							}
						} catch (...) {
							res = '0';
						}
					} while ((res == '0'));
					break;
				case 'c' :
					std::string nomFichier;
					do {
						std::cout << "Entrez le nom du fichier à charger ('q' pour revenir au menu principal) : ";
						std::cin >> nomFichier;
						if (nomFichier == "q") {
							res = '0';
						} else if(a->charger(nomFichier)) {
							res = '1';
							std::cout << *a << std::endl;
							a->finTour(); // le joueur fini son tour
							if (a->tourMaxAtteint()) {
								finDePartie = true;
							}
						} else {
							res = '2';
						}
					} while (res == '2');
					break;
			}
		} while (res == '0');
		
		while (!finDePartie) {
			// TO DO : faire les bons affichages
			a->jouerActions();
			if ((a->tourDeJeu == 1) || !(a->getMode())) {
			// On affiche l'état du jeu avant la création éventuelle d'unité si le joueur est en mode manuel
				std::cout << *a << std::endl;
			}
			if (a->baseDetruite()) {
				finDePartie = true;
			} else {
				a->finTour();
				/*if ((a->tourDeJeu == 1) && (a->getMode())){
				// On affiche l'état du jeu après la création éventuelle d'unité si le joueur est en mode automatique
					a->print();
				}*/
				if (a->tourMaxAtteint()) {
					finDePartie = true;
				}	
			}
		}
		finDePartie = false;
		a->resetAireDeJeu();
	} while (true);

	
	// TESTS (ajouts d'unités)
	/*Fantassin* u1 = new Fantassin(1);
	a->plateau[0] = u1;
	Archer* u2 = new Archer(1);
	a->plateau[1] = u2;
	Catapulte* u3 = new Catapulte(1);
	a->plateau[2] = u3;
	SuperSoldat* u4 = new SuperSoldat(10,1);
	a->plateau[3] = u4;
	Archer* u5 = new Archer(1);
	a->plateau[4] = u5;
	Archer* u6 = new Archer(1);
	a->plateau[5] = u6;
	Fantassin* u7 = new Fantassin(-1);
	a->plateau[11] = u7;*/

	// Sauvegarder un fichier de jeu :
	/*char* nomFichier = new char;
	std::cout << "Entrez le nom du fichier où sauver : ";
	std::cin >> nomFichier;
	a->sauvegarder(nomFichier);*/

	// Charger un fichier de jeu :
	/*char* nomFichier2 = new char;
	std::cout << "Entrez le nom du fichier à charger : ";
	std::cin >> nomFichier2;
	a->charger(nomFichier2);*/

	//a->print();

	delete a; //je crois qu'il faut aussi détruire le plateau

	return 0;
}
