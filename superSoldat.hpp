#ifndef SUPERSOLDAT_HPP
#define SUPERSOLDAT_HPP

#include "fantassin.hpp"

class SuperSoldat : public Fantassin {

	public:
		SuperSoldat(int pdv, int equipe) : Fantassin(pdv, equipe) {}
		~SuperSoldat();

		bool getAutreAction() const {return true;};
		char getNomUnite() const {return 'S';};

		// Renvoie un vecteur d'indices des unites vaincus
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur); // redefinition de celle de fantassin, car on ne va plus appeler la fonction aVaincuFantassin
		void deplace(Unite* plateau[12], int i);
};

#endif