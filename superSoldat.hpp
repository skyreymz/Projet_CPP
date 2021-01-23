#ifndef SUPERSOLDAT_HPP
#define SUPERSOLDAT_HPP

#include "fantassin.hpp"

class SuperSoldat : public Fantassin {
	
	bool autreAction = true;

	public:
		SuperSoldat(int pdv, int equipe) : Fantassin(pdv, equipe) {} // il ne veut pas directement appeler le constructeur du grand-pere Unite(pdv)... peut etre qu'on ne peut pas!
		~SuperSoldat();

		bool getAutreAction() {return true;};
		char getNomUnite() const {return 'S';};

		void setAutreAction(bool b) {autreAction = b;}; // Inutile mais obligatoire

		// Renvoie un vecteur d'indices des unites vaincus
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur); // redefinition de celle de fantassin, car on ne va plus appeler la fonction aVaincuFantassin
		void deplace(Unite* plateau[12], int i);
};

#endif