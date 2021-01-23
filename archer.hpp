#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	static int portee[3];

	bool autreAction = false;
	
	public:
		Archer(int equipe) : Unite(8, equipe) {}
		Archer(int pdv, int equipe) : Unite(pdv, equipe) {}
		~Archer();

		static int getPrix() {return prix;};
		bool getAutreAction() {return autreAction;};
		char getNomUnite() const {return 'A';};
		int getPrixDeces() {return prix/2;};

		void setAutreAction(bool b) {autreAction = b;}; // Inutile mais obligatoire

		// Renvoie une paire <bool, vecteur d'indices des unites vaincus> (true si et seulement si un fantassin a vaincu un autre fantassin)
		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i, Joueur* joueur);
};

#endif
