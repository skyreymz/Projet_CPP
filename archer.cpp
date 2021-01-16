#include <iostream>
#include "archer.hpp"

int Archer::prix = 12;
int Archer::atq = 3;
int Archer::portee[3] = {1,2,3};

Archer::~Archer() {}

int Archer::getPrix() {
    return prix;
}


//IL FAUDRA CHANGER LE bool camp en int = 1 ou -1 
std::pair<bool,std::vector<int>> Archer::attaque(Unite* plateau[12], int i) {
    for (int j=0; j<3; j++) {
        if (! (plateau[i + getCamp() * portee[j]] == nullptr) ) {
            if (plateau[i + getCamp() * portee[j]]->getCamp() != getCamp()) {
                plateau[i+ getCamp() * portee[j]]->setPV(-atq);
                if (plateau[i + getCamp() * portee[j]]->estVaincu()) {
                    return std::make_pair(false, std::vector<int>(1)={i+ getCamp() * portee[j]});
                }
                break;
            }
        }
    }
    return std::make_pair(false, std::vector<int>()={});
}