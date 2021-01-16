#include "aireDeJeu.hpp"
#include <string>

int main() {
	bool m = 0; // 0 signifie joueur contre joueur ; 1 signifie joueur contre ordinateur
	std::string mode = m ? "automatique":"manuel";
	std::cout << "MODE CHOISI : Joueur A (manuel) vs Joueur B (" + mode + ')' << std::endl;

	std::cout << "INSTANCIATION D'UNE AIRE DE JEU" << std::endl;
	AireDeJeu* a = new AireDeJeu(m);
	
	// TESTS
	Fantassin* f = new Fantassin(1);
	//std::cout << f.getInfos() << std::endl;
	a->plateau[0] = f;

	a->print();

	//a->nouveauTour();

	//a->print();

	/*char* nomFichier = new char;
	std::cout << "entrez le nom du fichier à charger : ";
	std::cin >> nomFichier;
	a->charger(nomFichier);

	a->print();

	delete a; //je crois qu'il faut aussi détruire le plateau
*/
	return 0;
}