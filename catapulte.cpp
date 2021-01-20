#include <iostream>
#include "catapulte.hpp"

int Catapulte::prix = 20;
int Catapulte::atq = 6;
std::pair<int,int> Catapulte::portee[3] = {std::make_pair(2,3), std::make_pair(3,4), std::make_pair(3,4)};

Catapulte::~Catapulte() {}

std::pair<bool,std::vector<int>> Catapulte::attaque(Unite* plateau[12], int i, Joueur* joueur) {
    int indiceMAX;
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    for (int j=0; j<3; j++) {

        if (j != 2) {

            if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].first) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].first) >= indiceMAX)) ) {
                if (! (plateau[i + getCamp() * portee[j].first] == nullptr) ) {
                    if (plateau[i + getCamp() * portee[j].first]->getCamp() != getCamp()) {

                        std::vector<int> vaincus;
                        plateau[i + getCamp() * portee[j].first]->setPV(-atq);
                        if (plateau[i + getCamp() * portee[j].first]->estVaincu()) {
                            vaincus.push_back(i + getCamp() * portee[j].first);
                        }

                        if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].second) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].second) >= indiceMAX)) ) {
                            if (! (plateau[i + getCamp() * portee[j].second] == nullptr) ) {
                                plateau[i + getCamp() * portee[j].second]->setPV(-atq);
                                if (plateau[i + getCamp() * portee[j].second]->estVaincu()) {
                                    vaincus.push_back(i + getCamp() * portee[j].second);
                                }
                            }
                            else if ( (i + getCamp() * portee[j].second) == indiceMAX ) {
                                joueur->setPvBase(-atq);
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( (i + getCamp() * portee[j].first) == indiceMAX ) {
                    joueur->setPvBase(-atq);
                }
            }
        }
        else {

            if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].second) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].second) >= indiceMAX)) ) {
                if (! (plateau[i + getCamp() * portee[j].second] == nullptr) ) {
                    if (plateau[i + getCamp() * portee[j].second]->getCamp() != getCamp()) {

                        std::vector<int> vaincus;
                        plateau[i + getCamp() * portee[j].second]->setPV(-atq);
                        if (plateau[i + getCamp() * portee[j].second]->estVaincu()) {
                            vaincus.push_back(i + getCamp() * portee[j].second);
                        }

                        if (! (plateau[i + getCamp() * portee[j].first] == nullptr) ) {
                            plateau[i + getCamp() * portee[j].first]->setPV(-atq);
                            if (plateau[i + getCamp() * portee[j].first]->estVaincu()) {
                                vaincus.push_back(i + getCamp() * portee[j].first);
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( (i + getCamp() * portee[j].second) == indiceMAX ) {
                    joueur->setPvBase(-atq);
                }
            }
        }
        
    }
    return std::make_pair(false, std::vector<int>()={});
}
