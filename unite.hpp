#ifndef UNITE_HPP
#define UNITE_HPP

#include <iostream>
#include <string>

class Unite {
	
	int pv;

	int camp; // 1 ou -1, permet de differencier les unites du joueur de gauche de ceux du joueur de droite
	

	public:
		Unite(int pdv, bool equipe) : pv(pdv), camp(equipe) {} 
		//rajouter dans ce constructeur et TOUS ceux qui en derivent par heritage, l'initialisation du camp (si jamais l'idee est bonne)
		virtual ~Unite()=0;

		virtual std::string getInfos() const;

		int getPV() const; // j'ai enlevé "virtual" car je pense que c'est nécesaire que quand on a de la redéfinition de méthode
		virtual int getCamp() const;

		virtual void dommages(int atq);
		virtual bool estVaincu();

};

#endif
