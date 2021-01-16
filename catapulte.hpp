#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include <iostream>
#include <utility>
#include "unite.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	static std::pair<int,int> portee[3];
	
	
	public:
		Catapulte(bool equipe) : Unite(12, equipe) {}
		~Catapulte();

		static int getPrix();

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // normalement c'est une redéfinition, sinon mon code est foutu pour faire l'action 1 
};

#endif
