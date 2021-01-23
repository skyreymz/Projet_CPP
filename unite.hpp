#ifndef UNITE_HPP
#define UNITE_HPP

#include <string>
#include <vector>
#include "joueur.hpp"

class Unite { // CLASSE ABSTRAITE
	
	int pv;
	int camp; // 1 (Unite du joueur A) ou -1 (Unite du joueur B)
	bool autreAction;

	public:
		Unite(int pdv, int equipe) : pv(pdv), camp(equipe), autreAction(true) {}
		Unite(int pdv, int equipe, bool oneMore) : pv(pdv), camp(equipe), autreAction(oneMore) {}
		virtual ~Unite()=0;

		// Méthodes de récupération/affichage de valeur des attributs
		int getPV() const {return pv;};
		bool estVaincu() {return (pv == 0);};
		int getCamp() const {return camp;};
		char getCampChar() const;
		virtual char getNomUnite() const = 0;
		virtual int getPrixDeces() = 0;
		virtual bool getAutreAction()const {return autreAction;};
		void afficheAttaqueUnite(char nomUnite, int atq, int position, Unite* cible, int positionCible) const;
		void afficheAttaqueBase(char nomUnite, int atq, int position) const;

		// Méthodes de modification de valeur des attributs
		int subPV(int atq); // Soutrait et retourne le nombre de points de vie soustrait
		void setAutreAction(bool b) {autreAction = b;};

		// Renvoie un vecteur d'indices des unites vaincus
		virtual std::vector<int> attaque(Unite* plateau[12], int i, Joueur* joueur) = 0;
		virtual void deplace(Unite* plateau[12], int i) = 0;
};

#endif
