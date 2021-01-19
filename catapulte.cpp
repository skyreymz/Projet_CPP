#include <iostream>
#include "catapulte.hpp"

int Catapulte::prix = 20;
int Catapulte::atq = 6;
std::pair<int,int> Catapulte::portee[3] = {std::make_pair(2,3), std::make_pair(3,4), std::make_pair(3,4)};

Catapulte::~Catapulte() {}

std::pair<bool,std::vector<int>> Catapulte::attaque(Unite* plateau[12], int i) {
    for (int j=0; j<3; j++) {

        if (j != 2) {
            if (! (plateau[i + getCamp() * portee[j].first] == nullptr) ) {
                if (plateau[i + getCamp() * portee[j].first]->getCamp() != getCamp()) {
                    plateau[i+ getCamp() * portee[j].first]->setPV(-atq);
                    plateau[i+ getCamp() * portee[j].second]->setPV(-atq);
                    autreAction = false;

                    std::vector<int> vaincus;
                    if (plateau[i + getCamp() * portee[j].first]->estVaincu()) {
                        vaincus.push_back(i+ getCamp() * portee[j].first);
                    }
                    if (plateau[i + getCamp() * portee[j].second]->estVaincu()) {
                        vaincus.push_back(i+ getCamp() * portee[j].second);
                    }
                    return std::make_pair(false, vaincus);
                
                    break;
                }
            }
        }
        else {
            if (! (plateau[i + getCamp() * portee[j].second] == nullptr) ) {
                if (plateau[i + getCamp() * portee[j].second]->getCamp() != getCamp()) {
                    plateau[i+ getCamp() * portee[j].second]->setPV(-atq);
                    plateau[i+ getCamp() * portee[j].first]->setPV(-atq);
                    autreAction = false;

                    std::vector<int> vaincus;
                    if (plateau[i + getCamp() * portee[j].second]->estVaincu()) {
                        vaincus.push_back(i+ getCamp() * portee[j].second);
                    }
                    if (plateau[i + getCamp() * portee[j].first]->estVaincu()) {
                        vaincus.push_back(i+ getCamp() * portee[j].first);
                    }
                    return std::make_pair(false, vaincus);

                    //break;
                }
            }
        }
        
    }
    std::cout << (plateau[0] == nullptr) << i; // "warning plateau & i isn't used"
    return std::make_pair(false, std::vector<int>()={});
}
