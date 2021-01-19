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

		void setJoueur(bool mode0, int argent0, int pvBase0) {mode = mode0; argent = argent0; pvBase = pvBase0;};

		bool getMode() const {return mode;};
		int getArgent() const {return argent;};
		int getPvBase() const {return pvBase;};
		void setMode(bool mod) {mode = mod;};
		void setArgent(int money) {argent += money;};
		void setPvBase(int atq) {pvBase += atq;}; // à renommer en setPvBase et faire attention à toutes les classes qui l'utilisent
		void detruireBase() {pvBase = 0;};
};

#endif
