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

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // normalement c'est une redéfinition, sinon mon code est foutu pour faire l'action 1 
};

#endif
