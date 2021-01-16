#include <iostream>
#include "catapulte.hpp"

int Catapulte::prix = 20;
int Catapulte::atq = 6;
//std::pair<int,int> Catapulte::portee[2] = {std::make_pair(2,3), std::make_pair(3,4)};

Catapulte::~Catapulte() {}

int Catapulte::getPrix() {
    return prix;
}

std::pair<bool,std::vector<int>> Catapulte::attaque(Unite* plateau[12], int i) {
	// TO DO
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
	return std::make_pair(false, std::vector<int>()={});
}