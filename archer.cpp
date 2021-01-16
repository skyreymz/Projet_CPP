#include <iostream>
#include "archer.hpp"

int Archer::prix = 12;
int Archer::atq = 3;
//int Archer::portee = {1,2,3};

Archer::~Archer() {}

int Archer::getPrix() {
    return prix;
}

std::pair<bool,std::vector<int>> Archer::attaque(Unite* plateau[12], int i) {
	// TO DO
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
	return std::make_pair(false, std::vector<int>()={});
}