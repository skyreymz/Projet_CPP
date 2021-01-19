#ifndef SUPERSOLDAT_HPP
#define SUPERSOLDAT_HPP

#include <iostream>
#include "fantassin.hpp"

class SuperSoldat : public Fantassin {
	
	bool autreAction = true;

	public:
		SuperSoldat(int pdv, int equipe) : Fantassin(pdv, equipe) {} // il ne veut pas directement appeler le constructeur du grand-pere Unite(pdv)... peut etre qu'on ne peut pas!
		~SuperSoldat();

		char getNomUnite() const {return 'S';};

		bool getAutreAction();

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // redefinition de celle de fantassin, car on ne va plus appeler la fonction aVaincuFantassin
};

#endif
