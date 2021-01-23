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

            if ( ((getCamp() == 1) && ((positionCibleFirst) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleFirst) >= indiceMAX)) ) {
                if (plateau[positionCibleFirst] != nullptr) {
                    if (plateau[positionCibleFirst]->getCamp() != getCamp()) {
                        afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleFirst], positionCibleFirst);

                        std::vector<int> vaincus;
                        plateau[positionCibleFirst]->subPV(atq);
                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(positionCibleFirst);
                        }

                        if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                            if (plateau[positionCibleSecond] != nullptr) {
                                afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleSecond], positionCibleSecond);
                                plateau[positionCibleSecond]->subPV(atq);
                                if (plateau[positionCibleSecond]->estVaincu()) {
                                    vaincus.push_back(positionCibleSecond);
                                }
                            }
                            else if ( (positionCibleSecond) == indiceMAX ) {
                                afficheAttaqueBase(this, getNomUnite(), atq, i);
                                joueur->subPvBase(atq);
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( positionCibleFirst == indiceMAX ) {
                    afficheAttaqueBase(this, getNomUnite(), atq, i);
                    joueur->subPvBase(atq);
                    autreAction = false;
                }
            }
        }
        else {

            if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                std::vector<int> vaincus;

                if (plateau[positionCibleSecond] != nullptr) {
                    if (plateau[positionCibleSecond]->getCamp() != getCamp()) {

                        afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleSecond], positionCibleSecond);
                        plateau[positionCibleSecond]->subPV(atq);
                        if (plateau[positionCibleSecond]->estVaincu()) {
                            vaincus.push_back(positionCibleSecond);
                        }
                        autreAction = false;
                    }
                }
                else if ( (positionCibleSecond) == indiceMAX ) {
                    afficheAttaqueBase(this, getNomUnite(), atq, i);
                    joueur->subPvBase(atq);
                    autreAction = false;
                }

                if (!autreAction) {
                    if (plateau[positionCibleFirst] != nullptr) {
                        afficheAttaqueUnite(this, getNomUnite(), atq, i, plateau[positionCibleFirst], positionCibleFirst);
                        plateau[positionCibleFirst]->subPV(atq);
                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(positionCibleFirst);
                        }
                    }
                }

                return std::make_pair(false, vaincus);
            }
        }
        
    }
    return std::make_pair(false, std::vector<int>()={});
}