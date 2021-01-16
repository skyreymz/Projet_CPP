#ifndef ARCHER_HPP
#define ARCHER_HPP

#include <iostream>
#include "unite.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	//static int portee[3];
	
	
	public:
		Archer(bool equipe) : Unite(8, equipe) {}
		~Archer();

		static int getPrix();

		void attaque(); // normalement c'est une redéfinition, sinon mon code est foutu pour faire l'action 1 

};

#endif
