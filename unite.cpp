#include <iostream>
#include "unite.hpp"

Unite::~Unite() {}

int Unite::getPV() const {
	return pv;
}

bool Unite::getCamp() const {
	return camp;
}

std::string Unite::getInfos() const {
	if (!camp) {
		return "A";
	} else {
		return "B";
	}
}

void Unite::setPV(int atq) {
	pv -= atq;
}

bool Unite::estVaincu() {
	if (pv <= 0) {
		return true;
	}
	else{
		return false;
	}
}

std::pair<bool,std::vector<int>> Unite::attaque(Unite* plateau[12], int i) { //pour éviter que le compilateur râle mais cette méthode inutile car Unite est abstraite
	//TO DO
	std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
	return std::make_pair(false, std::vector<int>()={});
}