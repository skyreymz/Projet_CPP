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
        int positionCibleFirst = i + getCamp() * portee[j].first;
        int positionCibleSecond = i + getCamp() * portee[j].second;

        if (j != 2) {

            if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].first) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].first) >= indiceMAX)) ) {
                if (plateau[positionCibleFirst] != nullptr) {
                    if (plateau[positionCibleFirst]->getCamp() != getCamp()) {
                        afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleFirst], positionCibleFirst);

                        std::vector<int> vaincus;
                        plateau[positionCibleFirst]->setPV(-atq);
                        autreAction = false;
                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(i + getCamp() * portee[j].first);
                        }

                        if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].second) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].second) >= indiceMAX)) ) {
                            if (plateau[positionCibleSecond] != nullptr) {
                                afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleSecond], positionCibleSecond);
                                plateau[positionCibleSecond]->setPV(-atq);
                                autreAction = false;
                                if (plateau[positionCibleSecond]->estVaincu()) {
                                    vaincus.push_back(i + getCamp() * portee[j].second);
                                }
                            }
                            else if ( (i + getCamp() * portee[j].second) == indiceMAX ) {
                                afficheAttaqueBase(this, getNomUnite(), atq, i);
                                joueur->setPvBase(-atq);
                                autreAction = false;
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( (i + getCamp() * portee[j].first) == indiceMAX ) {
                    afficheAttaqueBase(this, getNomUnite(), atq, i);
                    joueur->setPvBase(-atq);
                    autreAction = false;
                }
            }
        }
        else {

            if ( ((getCamp() == 1) && ((i + getCamp() * portee[j].second) <= indiceMAX)) || ((getCamp() == -1) && ((i + getCamp() * portee[j].second) >= indiceMAX)) ) {
                if (plateau[positionCibleSecond] != nullptr) {
                    if (plateau[positionCibleSecond]->getCamp() != getCamp()) {
                        afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleSecond], positionCibleSecond);

                        std::vector<int> vaincus;
                        plateau[positionCibleSecond]->setPV(-atq);
                        autreAction = false;
                        if (plateau[positionCibleSecond]->estVaincu()) {
                            vaincus.push_back(i + getCamp() * portee[j].second);
                        }

                        if (plateau[positionCibleFirst] != nullptr) {
                            afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleFirst], positionCibleFirst);
                            plateau[positionCibleFirst]->setPV(-atq);
                            autreAction = false;
                            if (plateau[positionCibleFirst]->estVaincu()) {
                                vaincus.push_back(i + getCamp() * portee[j].first);
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( (i + getCamp() * portee[j].second) == indiceMAX ) {
                    afficheAttaqueBase(this, getNomUnite(), atq, i);
                    joueur->setPvBase(-atq);
                    autreAction = false;
                }
            }
        }
        
    }
    return std::make_pair(false, std::vector<int>()={});
}
