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