#include <iostream>
#include "fantassin.hpp"
#include <string>

int Fantassin::prix = 10;
int Fantassin::atq = 4;
//int Fantassin::portee = {1};

Fantassin::~Fantassin() {}

std::string Fantassin::getInfos() const {
	return "F("+Unite::getInfos()+")";
}
