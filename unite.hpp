#ifndef UNITE_HPP
#define UNITE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Unite {
	
	int pv;

	bool camp; // permet de differencier les unites du joueur de gauche de ceux du joueur de droite
	

	public:
		Unite(int pdv, bool equipe) : pv(pdv), camp(equipe) {} 
		//rajouter dans ce constructeur et TOUS ceux qui en derivent par heritage, l'initialisation du camp (si jamais l'idee est bonne)
		virtual ~Unite()=0;

		virtual std::string getInfos() const;

		int getPV() const; // j'ai enlevé "virtual" car je pense que c'est nécesaire que quand on a de la redéfinition de méthode
		bool getCamp() const;

		void setPV(int atq);
		bool estVaincu();

		// Renvoie une paire <true, vecteur d'indices des unites vaincus>, true si et seulement si un fantassin a vaincu un autre fantassin
		virtual std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i);

		virtual int getPrixDeces();
		virtual bool getAutreAction();

};

#endif
