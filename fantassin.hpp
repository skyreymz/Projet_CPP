#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include <iostream>
#include "unite.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];

	bool autreAction = true;
	
	
	public:
		Fantassin(int equipe) : Unite(10, equipe) {}
		Fantassin(int pdv, int equipe) : Unite(pdv, equipe) {}
		~Fantassin();

		std::string getInfos() const {return "F("+Unite::getInfos()+")";};
		bool aVaincuFantassin(Unite* unite);

		static int getPrix() {return prix;};
		static int getAtq() {return atq;};
		static int getPortee() {return portee[0];}; 
		int getPrixDeces() {return prix/2;}; // utile pour SuperSoldat qui l'herite, car le prix est statique

		virtual bool getAutreAction() {return autreAction;}; // virtual car on va la redéfinir pour le SuperSoldat pour que celui-ci ne recupere PAS le bool autreAction hérité de Fantassin mais bien le SIEN qui sera tjs true !

		std::pair<bool,std::vector<int>> attaque(Unite* plateau[12], int i); // ceci est une redéfinition car la méthode de la mère est virtual
};

#endif
