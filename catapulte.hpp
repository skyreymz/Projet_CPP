#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	static std::pair<int,int> portee[3];
	
	
	public:
		Catapulte(int equipe, int pdv = 12) : Unite(equipe, pdv, true) {}
		~Catapulte();

		// Méthodes de récupération de valeur des attributs
		static int getPrix() {return prix;};
		bool getAutreAction() const {return Unite::getAutreAction();};
		char getNomUnite() const {return 'C';};
		int getPrixDeces() {return prix/2;};

		// Méthodes pour effectuer les actions de Catapulte
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur); // Renvoie un vecteur d'indices des unites vaincus
		void deplace(Unite* plateau[12], int i);
};

#endif