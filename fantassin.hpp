#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];

	public:
		Fantassin(int equipe) : Unite(10, equipe) {}
		Fantassin(int pdv, int equipe) : Unite(pdv, equipe) {}
		Fantassin(int pdv, int equipe, bool oneMore) : Unite(pdv, equipe, oneMore) {}
		~Fantassin();

		// Méthodes de récupération/affichage de valeur des attributs
		static int getPrix() {return prix;};
		static int getAtq() {return atq;};
		static int getPortee() {return portee[0];};
		bool getAutreAction() const {return Unite::getAutreAction();};
		char getNomUnite() const {return 'F';};
		int getPrixDeces() {return prix/2;}; // pour la classe SuperSoldat

		// Renvoie un vecteur d'indices des unites vaincus
		std::vector<int> attaque(Unite* plateau[12], int i, Joueur* Joueur);
		void deplace(Unite* plateau[12], int i);

		bool aVaincuFantassin(Unite* unite);
};

#endif
