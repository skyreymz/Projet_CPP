#include <iostream>
#include "unite.hpp"

Unite::~Unite() {}

std::string Unite::getInfos() const {
	if (camp == 1) {
		return "A";
	} else {
		return "B";
	}
}

std::pair<bool,std::vector<int>> Unite::attaque(Unite* plateau[12], int i) { //pour éviter que le compilateur râle mais cette méthode inutile car Unite est abstraite
	//TO DO
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
	return std::make_pair(false, std::vector<int>()={});
}