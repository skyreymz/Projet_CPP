#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	static std::pair<int,int> portee[3];
	
	
	public:
		Catapulte(int equipe) : Unite(12, equipe, true) {}
		Catapulte(int pdv, int equipe) : Unite(pdv, equipe, true) {}
		~Catapulte();

		static int getPrix() {return prix;};
		bool getAutreAction() const {return Unite::getAutreAction();};
		char getNomUnite() const {return 'C';};
		int getPrixDeces() {return prix/2;};

		// Renvoie un vecteur d'indices des unites vaincus
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur);
		void deplace(Unite* plateau[12], int i);
};

#endif