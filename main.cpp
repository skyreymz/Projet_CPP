#include "aireDeJeu.hpp"

int main() {
	std::cout << "\nPROJET C++ | THIEFFRY Rémy | VU Tri-Man William" << std::endl;
	std::cout << " _____   ______   _____     _____   _____     _       _   _____   _____\n";
	std::cout << "|  _  | |  ____| |  ___|   |  _  | |  ___|   | |     | | |  _  | |  _  |\n";
	std::cout << "| |_| | | |  __  | |__     | | | | | |__     | |  _  | | | |_| | | |_| |\n";
	std::cout << "|  _  | | | |_ | |  __|    | | | | |  __|    | | | | | | |  _  | |    _|\n";
	std::cout << "| | | | | |__| | | |___    | |_| | | |       | |_| |_| | | | | | | |\\ \\\n";
	std::cout << "|_| |_| |______| |_____|   |_____| |_|       |_________| |_| |_| |_| \\_\\\n";

	AireDeJeu* a = new AireDeJeu();

	bool finDePartie = false;
	std::string resString;
	char res;
	do {
		do {
			std::cout << "\nCommencer une Nouvelle partie ('n') / Charger une partie ('c') / Quitter ('q') : ";
			std::cin >> resString;
			if (resString.length() != 1) {
				res = '0';
			} else {
				res = resString.at(0);
			}
			switch (res) {
				case 'n' :
					do {
						std::cout << "Humain contre Humain ('h') / Humain contre IA ('i') : ";
						std::cin >> resString;
						if (resString.length() == 1) {
							res = resString.at(0);
						}
						switch (res) {
							case 'h':
								[[fallthrough]];
							case 'i':
								a->setMode(res == 'i');
								break;
							default :
								std::cerr << "Caractère(s) non reconnu(s)" << std::endl;
								res = '2';
								break;
						}
					} while (res == '2');

					do {
						std::cout << "Entrez le nombre maximum de tours (au moins 1) : ";
						std::cin >> resString;
						try {
							int nbTourMaxInt = std::stoi(resString);
							if (nbTourMaxInt < 1) {
								std::cerr << "Le nombre de tour ne peut pas être négatif" << std::endl;
								res = '2';
							} else {
								a->setNbToursMax(nbTourMaxInt);
								a->afficherTour();
								a->addArgent(8);
								std::cout << "\nLes joueurs ont gagné 8 pièces d'or (nouveau tour)" << std::endl;
								res = '1';
							}
						} catch (...) {
							std::cerr << "Caractère(s) non reconnu(s)" << std::endl;
							res = '2';
						}
					} while ((res == '2'));
					break;

				case 'c' :
					do {
						std::cout << "Entrez le nom du fichier à charger ('r' pour revenir au menu principal) : ";
						std::cin >> resString;
						if (resString == "r") {
							res = '0';
						} else if(a->charger(resString)) {
							a->afficherTour();
							res = '1';
						} else {
							res = '2';
						}
					} while (res == '2');
					break;

				case 'q' :
					res = '3'; // quitter l'application
					break;

				default:
					std::cerr << "Caractère(s) non reconnu(s)" << std::endl;
					res = '0';
					break;
			}
			// Si (res == '0') : retour au menu principal
			// Si (res == '1') : nouvelle partie lancée
			// Si (res == '2') : boucle dans les "sous-boucles"
			// Si (res == '3') : quitte l'application
		} while (res == '0');

		if (res == '1') {
			
			std::cout << *a << std::endl;

			if (!a->finTour()) { // Si le joueur quitte la partie en cours
				finDePartie = true;
			} else if (a->tourMaxAtteint()) {
				finDePartie = true;
			}

			while (!finDePartie) {
				if (a->getTourDeJeu() == 1) {
					a->incrNbTourActuel();
					a->afficherTour();
					a->addArgent(8);
					std::cout << "\nLes joueurs ont gagné 8 pièces d'or (nouveau tour)" << std::endl;
				} else {
					a->afficherTour();
				}
				a->jouerActions();
				std::cout << *a << std::endl;

				if (a->baseDetruite()) {
					finDePartie = true;
				} else {
					if (!a->finTour()) { // Si le joueur quitte la partie en cours
						finDePartie = true;
					} else if (a->tourMaxAtteint()) {
						finDePartie = true;
					}	
				}
			}
			
			finDePartie = false;
			a->reset();
		}
		
	} while (res != '3');

	delete a;
	return 0;
}
