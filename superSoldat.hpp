#ifndef SUPERSOLDAT_HPP
#define SUPERSOLDAT_HPP

#include <iostream>
#include "fantassin.hpp"

class SuperSoldat : public Fantassin {
	
	
	public:
		SuperSoldat(int pdv) : Fantassin(pdv) {} // il ne veut pas directement appeler le constructeur du grand-pere Unite(pdv)... peut etre qu'on ne peut pas!
		~SuperSoldat();
};

#endif
