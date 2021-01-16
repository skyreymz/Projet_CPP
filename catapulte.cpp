#include <iostream>
#include "catapulte.hpp"

int Catapulte::prix = 20;
int Catapulte::atq = 6;
//std::pair<int,int> Catapulte::portee[2] = {std::make_pair(2,3), std::make_pair(3,4)};

Catapulte::~Catapulte() {}

int Catapulte::getPrix() {
    return prix;
}
