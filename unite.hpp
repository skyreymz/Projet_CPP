#ifndef UNITE_HPP
#define UNITE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "joueur.hpp"

class Unite { // CLASSE ABSTRAITE
	
	int camp; // 1 (Unite du joueur A) ou -1 (Unite du joueur B)
	int pv;
	bool autreAction; // true si l'unite n'a pas deja attaque, false sinon


	public:
		Unite(int equipe, int pdv, bool oneMore) : camp(equipe), pv(pdv), autreAction(oneMore) {}
		virtual ~Unite()=0;

		// Méthodes de récupération de valeur des attributs
		int getCamp() const {return camp;};
		char getCampChar() const;
		int getPV() const {return pv;};
		bool estVaincu() {return (pv == 0);};
		virtual bool getAutreAction()const {return autreAction;};
		virtual char getNomUnite() const = 0;
		virtual int getPrixDeces() = 0;
		friend std::ostream &operator<<(std::ostream &flux, const Unite &u); // Affichage du Nom d'unité et de son camps

		// Méthodes de modification de valeur des attributs
		int subPV(int atq);
		void setAutreAction(bool b) {autreAction = b;};

		// Méthodes pour effectuer les actions des Unités
		virtual std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur) = 0;
		virtual void deplace(Unite* plateau[12], int i) = 0;
		
		// Méthodes pour l'affichage des attaques des Unités
		void afficheAttaqueUnite(char nomUnite, int atq, int position, Unite* cible, int positionCible) const;
		void afficheAttaqueBase(char nomUnite, int atq, int position) const;
};

#endif
