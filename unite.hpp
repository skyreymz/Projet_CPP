#ifndef UNITE_HPP
#define UNITE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Unite {
	
	int pv;

	int camp; // 1 ou -1, permet de differencier l'unite du joueur de gauche de celui de droite
	

	public:
		Unite(int pdv, int equipe) : pv(pdv), camp(equipe) {} 
		
		virtual ~Unite()=0;

		virtual std::string getInfos() const;

		int getPV() const {return pv;};
		int getCamp() const {return camp;};

		void setPV(int atq) {pv -= atq;};
		bool estVaincu() {return (pv <= 0);};

		// Renvoie une paire <true, vecteur d'indices des unites vaincus>, true si et seulement si un fantassin a vaincu un autre fantassin
		virtual std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i);

		virtual int getPrixDeces() {return 0;}; // pour polymorphisme
		virtual bool getAutreAction() {return 0;}; // pour polymorphisme
};

#endif
