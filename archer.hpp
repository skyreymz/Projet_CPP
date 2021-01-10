#ifndef ARCHER_HPP
#define ARCHER_HPP

#include <iostream>
#include "unite.hpp"

class Archer : public Unite {
	
	static int prix;
	static int atq;
	static int portee[3];
	
	
	public:
		Archer() : Unite(8) {}
		~Archer();

};

#endif
