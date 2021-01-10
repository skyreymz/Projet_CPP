#ifndef FANTASSIN_HPP
#define FANTASSIN_HPP

#include <iostream>
#include "unite.hpp"

class Fantassin : public Unite {
	
	static int prix;
	static int atq;
	static int portee[1];
	
	
	public:
		Fantassin() : Unite(10) {}
		Fantassin(int pdv) : Unite(pdv) {} // Pour le Super-Soldat
		~Fantassin();


};

#endif
