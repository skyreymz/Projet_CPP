#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <iostream>

class Joueur {
	
	int argent;
	int pvBase;

	
	public:
		Joueur(int depart = 50) : argent(depart), pvBase(100) {}
		~Joueur();
		
		
};

#endif
