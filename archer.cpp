#include <iostream>
#include "archer.hpp"

int Archer::prix = 12;
int Archer::atq = 3;
int Archer::portee[3] = {1,2,3};

Archer::~Archer() {}

int Archer::getPrix() {
    return prix;
}