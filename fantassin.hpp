#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];

	public:
		Fantassin(int equipe, int pdv = 10, bool oneMore = true) : Unite(equipe, pdv, oneMore) {}
		~Fantassin();

		// Méthodes de récupération de valeur des attributs
		static int getPrix() {return prix;};
		static int getAtq() {return atq;};
		static int getPortee() {return portee[0];};
		bool getAutreAction() const {return Unite::getAutreAction();};
		char getNomUnite() const {return 'F';};
		int getPrixDeces() {return prix/2;}; // pour la classe SuperSoldat

		// Méthodes pour effectuer les actions de Fantassin
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* Joueur); // Renvoie un vecteur d'indices des unites vaincus
		bool aVaincuFantassin(Unite* unite);
		void deplace(Unite* plateau[12], int i);
};

#endif
