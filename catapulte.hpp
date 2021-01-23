#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

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

		static int getPrix() {return prix;};
		bool getAutreAction() {return autreAction;};
		char getNomUnite() const {return 'C';};
		int getPrixDeces() {return prix/2;};

		void setAutreAction(bool b) {autreAction = b;};

		// Renvoie une paire <bool, vecteur d'indices des unites vaincus> (true si et seulement si un fantassin a vaincu un autre fantassin)
		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i, Joueur* joueur);
};

#endif