#include <iostream>
#include "unite.hpp"

Unite::~Unite() {}

int Unite::getPV() {
	return pv;
}

int Unite::getCamp() {
	return camp;
}

void Unite::dommages(int atq) {
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