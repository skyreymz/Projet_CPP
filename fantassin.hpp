#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include <iostream>
#include "unite.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];
	
	
	public:
		Fantassin(bool equipe) : Unite(10, equipe) {}
		Fantassin(int pdv, bool equipe) : Unite(pdv, equipe) {} // Pour le Super-Soldat
		~Fantassin();

		std::string getInfos() const;
		bool aVaincuFantassin(Unite* unite);

		static int getPrix();

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual
};

#endif
