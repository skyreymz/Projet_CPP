#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include <iostream>
#include <utility>
#include "unite.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	static std::pair<int,int> portee[3];

	bool autreAction = true;
	
	
	public:
		Catapulte(int equipe) : Unite(12, equipe) {}
		~Catapulte();

		static int getPrix();
		int getPrixDeces();

		bool getAutreAction();

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual
};

#endif
