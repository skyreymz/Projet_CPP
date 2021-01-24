#ifndef JOUEUR_HPP
#define JOUEUR_HPP

class Joueur {
	
	bool mode; // 0 (manuel) ou 1 (automatique)
	int argent;
	int pvBase;

	
	public:
		Joueur(int mod = 0, int depart = 2) : mode(mod), argent(depart), pvBase(100) {}
		~Joueur();

		// Méthodes de récupération de valeur des attributs
		bool getMode() const {return mode;};
		int getArgent() const {return argent;};
		int getPvBase() const {return pvBase;};

		// Méthodes de modification de valeur des attributs
		void setJoueur(bool mode0, int argent0, int pvBase0) {mode = mode0; argent = argent0; pvBase = pvBase0;};
		void setMode(bool mod) {mode = mod;};
		void addArgent(int money) {argent += money;};
		int subPvBase(int atq); // Soutrait et retourne le nombre de points de vie soustrait
};

#endif
