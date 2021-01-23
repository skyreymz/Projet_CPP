#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include "unite.hpp"
#include "joueur.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];

	bool autreAction = true;
	
	public:
		Fantassin(int equipe) : Unite(10, equipe) {}
		Fantassin(int pdv, int equipe) : Unite(pdv, equipe) {}
		~Fantassin();

		// Méthodes de récupération/affichage de valeur des attributs
		static int getPrix() {return prix;};
		static int getAtq() {return atq;};
		static int getPortee() {return portee[0];};
		virtual bool getAutreAction() {return autreAction;};
		char getNomUnite() const {return 'F';};
		int getPrixDeces() {return prix/2;}; // pour la classe SuperSoldat

		virtual void setAutreAction(bool b) {autreAction = b;};

		// Renvoie une paire <bool, vecteur d'indices des unites vaincus> (true si et seulement si un fantassin a vaincu un autre fantassin)
		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i, Joueur* Joueur);

		bool aVaincuFantassin(Unite* unite);
};

#endif
