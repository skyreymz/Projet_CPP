#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	static int portee[3];
	
	public:
		Archer(int equipe, int pdv = 8) : Unite(equipe, pdv, false) {}
		~Archer();

		// Méthodes de récupération de valeur des attributs
		static int getPrix() {return prix;};
		bool getAutreAction() const {return false;};
		char getNomUnite() const {return 'A';};
		int getPrixDeces() {return prix/2;};

		// Méthodes pour effectuer les actions de Archer
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur); // Renvoie un vecteur d'indices des unites vaincus
		void deplace(Unite* plateau[12], int i);
};

#endif
