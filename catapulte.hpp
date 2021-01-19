#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include <iostream>
#include <utility>
#include "unite.hpp"
#include "joueur.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	static std::pair<int,int> portee[3];

	bool autreAction = true;
	
	
	public:
		Catapulte(int equipe) : Unite(12, equipe) {}
		Catapulte(int pdv, int equipe) : Unite(pdv, equipe) {}
		~Catapulte();

		char getNomUnite() const {return 'C';};
		static int getPrix() {return prix;};
		int getPrixDeces() {return prix/2;};

		bool getAutreAction() {return autreAction;};

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i, Joueur* joueur); // ceci est une redéfinition car la méthode de la mère est virtual
};

#endif
