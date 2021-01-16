#include <iostream>
#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}

std::pair<bool,std::vector<int>> SuperSoldat::attaque(Unite* plateau[12], int i) {
	// TO DO
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
	return std::make_pair(false, std::vector<int>()={});
}