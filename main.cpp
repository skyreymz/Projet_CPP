#include "aireDeJeu.hpp"
#include <string>

int main() {
	bool m = 0; // 0 signifie joueur contre joueur ; 1 signifie joueur contre ordinateur
	std::string mode = m ? "automatique":"manuel";
	std::cout << "MODE CHOISI : Joueur A (manuel) vs Joueur B (" + mode + ')' << std::endl;

	std::cout << "INSTANCIATION D'UNE AIRE DE JEU" << std::endl;
	AireDeJeu* a = new AireDeJeu(m);
	
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

	// DEROULEMENT DU JEU
	/*while(!finDeJeu()) {
		jouerTour();
	}*/
	a->print();
	//a->nouveauTour();
	//a->print();

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

	a->print();

	delete a; //je crois qu'il faut aussi détruire le plateau

	return 0;
}