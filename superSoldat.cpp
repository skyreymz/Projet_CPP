#include <iostream>
#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}


//IL FAUDRA CHANGER LE bool camp en int = 1 ou -1
std::pair<bool,std::vector<int>> SuperSoldat::attaque(Unite* plateau[12], int i) {
    if (! (plateau[i + getCamp() * getPortee()] == nullptr) ) {
        if (plateau[i + getCamp() * getPortee()]->getCamp() != getCamp()) {
            plateau[i + getCamp() * getPortee()]->setPV(-getAtq());
            
            if (plateau[i + getCamp() * getPortee()]->estVaincu()) {
            	return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * getPortee()});
            }
        }
    }
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
    return std::make_pair(false, std::vector<int>()={});
}