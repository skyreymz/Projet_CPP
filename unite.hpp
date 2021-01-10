#ifndef UNITE_HPP
#define UNITE_HPP

#include <iostream>

class Unite {
	
	int pv;

	int camp; // 0 ou 1, permet de differencier les unites du joueur de gauche de ceux du joueur de droite
	

	public:
		Unite(int pdv  /* , int equipe */) : pv(pdv) /* , camp(equipe) */ {} 
		//rajouter dans ce constructeur et TOUS ceux qui en derivent par heritage, l'initialisation du camp (si jamais l'idee est bonne)
		virtual ~Unite()=0;

		virtual int getPV();
		virtual int getCamp();

};

#endif
