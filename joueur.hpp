#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <iostream>

class Joueur {
	
	bool mode; // 0 signifie manuel, 1 signifie automatique
	int argent;
	int pvBase;

	
	public:
		Joueur(int mod = 0, int depart = 50) : mode(mod), argent(depart), pvBase(100) {}
		~Joueur();

		int getPvBase() const {return pvBase;};
		int getArgent() const {return argent;};
		void setArgent(int money) {argent += money;};
		void dommages(int atq) {pvBase -= atq;};
};

#endif