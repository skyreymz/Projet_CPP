#include <iostream>
#include "unite.hpp"

Unite::~Unite() {}

int Unite::getPV() const {
	return pv;
}

int Unite::getCamp() const {
	return camp;
}

std::string Unite::getInfos() const {
	if (!camp) {
		return "A";
	} else {
		return "B";
	}
}