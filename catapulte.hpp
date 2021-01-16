#ifndef CATAPULTE_HPP
#define CATAPULTE_HPP

#include <iostream>
#include <utility>
#include "unite.hpp"

class Catapulte : public Unite {
	
	static int prix;
	static int atq;
	//static std::pair<int,int> portee[2];
	
	
	public:
		Catapulte(bool equipe) : Unite(12, equipe) {}
		~Catapulte();
};

#endif
