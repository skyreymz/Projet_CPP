#ifndef SUPERSOLDAT_HPP
#define SUPERSOLDAT_HPP

#include "fantassin.hpp"

class SuperSoldat : public Fantassin {


	public:
		SuperSoldat(int equipe, int pdv) : Fantassin(equipe, pdv, true) {}
		~SuperSoldat();

		// Méthodes de récupération de valeur des attributs
		bool getAutreAction() const {return true;};
		char getNomUnite() const {return 'S';};

		// Méthodes pour effectuer les actions deSuperSoldat
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur); // Redéfinition de celle de Fantassin car on n'appelle plus la méthode aVaincuFantassin
		void deplace(Unite* plateau[12], int i); // Redéfinition de celle de Fantassin car on instancie un SuperSoldat
};

#endif