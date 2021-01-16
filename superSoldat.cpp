#include <iostream>
#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}


//IL FAUDRA CHANGER LE bool camp en int = 1 ou -1
std::pair<bool,std::vector<int>> Fantassin::attaque(Unite* plateau[12], int i) {
    if (! (plateau[i + getCamp() * portee[0]] == nullptr) ) {
        if (plateau[i + getCamp() * portee[0]]->getCamp() != getCamp()) {
            plateau[i + getCamp() * portee[0]]->setPV(-atq);
            
            if (plateau[i + getCamp() * portee[0]]->estVaincu()) {
            	return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * portee[0]});
            }
        }
    }
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
    return std::make_pair(false, std::vector<int>()={});
}