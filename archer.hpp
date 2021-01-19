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
		Archer(int equipe) : Unite(8, equipe) {}
		Archer(int pdv, int equipe) : Unite(pdv, equipe) {}
		~Archer();

		char getNomUnite() const {return 'A';};
		static int getPrix() {return prix;};
		int getPrixDeces() {return prix/2;};

		bool getAutreAction() {return autreAction;};

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual

};

#endif
