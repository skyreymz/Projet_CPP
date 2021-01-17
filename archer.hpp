#ifndef ARCHER_HPP
#define ARCHER_HPP

#include <iostream>
#include "unite.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	static int portee[3];

	bool autreAction = false; // pas le choix de lui en donner un même s'il restera tjs à false, pour pouvoir faire du polymorphisme
	
	
	public:
		Archer(bool equipe) : Unite(8, equipe) {}
		~Archer();

		static int getPrix();
		int getPrixDeces();

		bool getAutreAction();

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual

};

#endif
