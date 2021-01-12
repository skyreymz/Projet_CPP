#include "aireDeJeu.hpp"

int main() {
	bool mode = 0; // 0 signifie joueur contre joueur ; 1 signifie joueur contre ordinateur

	std::cout << "INSTANCIATION D'UNE AIRE DE JEU" << std::endl;
	AireDeJeu* a = new AireDeJeu(0, 100, mode);
	a->print();

	
	return 0;
}