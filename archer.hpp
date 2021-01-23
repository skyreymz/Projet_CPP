#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	static int portee[3];
	
	public:
		Archer(int equipe) : Unite(8, equipe, false) {}
		Archer(int pdv, int equipe) : Unite(pdv, equipe, false) {}
		~Archer();

		static int getPrix() {return prix;};
		bool getAutreAction() const {return false;};
		char getNomUnite() const {return 'A';};
		int getPrixDeces() {return prix/2;};

		// Renvoie un vecteur d'indices des unites vaincus
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur);
		void deplace(Unite* plateau[12], int i);
};

#endif
