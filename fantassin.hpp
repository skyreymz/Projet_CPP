#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include <iostream>
#include "unite.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];

	bool autreAction;
	
	
	public:
		Fantassin(int equipe) : Unite(10, equipe) {}
		Fantassin(int pdv, int equipe) : Unite(pdv, equipe) {} // Pour le Super-Soldat
		~Fantassin();

		std::string getInfos() const {return "F("+Unite::getInfos()+")";};
		bool aVaincuFantassin(Unite* unite);

		static int getPrix() {return prix;};
		int getPrixDeces() {return prix/2;};

		static int getAtq() {return atq;};
		static int getPortee() {return portee[0];};

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual
};

#endif
