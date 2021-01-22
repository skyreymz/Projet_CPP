#include "aireDeJeu.hpp"
#include <string>

int main() {
	std::cout << "\nProjet C++ : Age of War" << std::endl;

	//INSTANCIATION D'UNE AIRE DE JEU
	AireDeJeu* a = new AireDeJeu();

	bool finDePartie = false;
	char res;
	std::string nomFichier; // nom du fichier pour charger une partie
	do {
		do {
			std::cout << "\nCommencer une Nouvelle partie ('n') / Charger une partie ('c') / Quitter ('q') : ";
			std::cin >> res;
			switch (res) {
				case 'n' :
					do {
						std::cout << "Joueur contre Joueur ('j') / Joueur contre IA ('m') : ";
						std::cin >> res;
						switch (res) {
							case 'j':
								a->setMode(false);
								a->setArgent(8);
								break;
							case 'm':
								a->setMode(true);
								a->setArgent(8);
								break;
							default :
								std::cerr << "Caractère incorrect" << std::endl;
								res = '2';
								break;
						}
					} while (res == '2');

					do {
						std::string nbTourMaxString;
						std::cout << "Entrez le nombre maximum de tours (au moins 1) : ";
						std::cin >> nbTourMaxString;
						try {
							int nbTourMaxInt = std::stoi(nbTourMaxString);
							if (nbTourMaxInt < 1) {
								std::cerr << "Le nombre de tour ne peut pas être négatif" << std::endl;
								res = '2';
							} else {
								a->setNbToursMax(nbTourMaxInt);
								res = '1';
							}
						} catch (...) {
							std::cerr << "Caractère incorrect" << std::endl;
							res = '2';
						}
					} while ((res == '2'));
					break;

				case 'c' :
					do {
						std::cout << "Entrez le nom du fichier à charger ('r' pour revenir au menu principal) : ";
						std::cin >> nomFichier;
						if (nomFichier == "r") {
							res = '0';
						} else if(a->charger(nomFichier)) {
							res = '1';
						} else {
							res = '2';
						}
					} while (res == '2');
					break;

				case 'q' :
					res = '3'; // quitter l'appilcation
					break;

				default:
					std::cerr << "Caractère incorrect" << std::endl;
					res = '0';
					break;
			}
			// Si (res == '0') : retour au menu principal
			// Si (res == '1') : partie lancée
			// Si (res == '2') : boucle dans les "sous-boucles"
			// Si (res == '3') : quitte l'application
		} while (res == '0');


		if (res == '1') {
			a->afficherInfos();
			std::cout << *a << std::endl;

			a->finTour();
			if (a->tourMaxAtteint()) {
				finDePartie = true;
			}
			
			while (!finDePartie) {
				a->afficherInfos();

				a->jouerActions();
				//if ((a->tourDeJeu == 1) || !(a->getMode())) {
				// On affiche l'état du jeu avant la création éventuelle d'unité si le joueur est en mode manuel
					std::cout << *a << std::endl;
				//}

				if (a->baseDetruite()) {
					finDePartie = true;
				} else {
					a->finTour();
					/*f ((a->tourDeJeu == 1) && (a->getMode())){
					// On affiche l'état du jeu après la création éventuelle d'unité si le joueur est en mode automatique
						std::cout << *a << std::endl;
					}*/
					if (a->tourMaxAtteint()) {
						finDePartie = true;
					}	
				}
			}
			
			finDePartie = false;
			a->reset();
		}

		
	} while (res != '3');

	
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
