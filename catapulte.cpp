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
        int pvRetire;

        if (j != 2) {

            if ( ((getCamp() == 1) && ((positionCibleFirst) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleFirst) >= indiceMAX)) ) {
                if (plateau[positionCibleFirst] != nullptr) {
                    if (plateau[positionCibleFirst]->getCamp() != getCamp()) {
                        pvRetire = plateau[positionCibleFirst]->subPV(atq);
                        afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCibleFirst], positionCibleFirst);

                        std::vector<int> vaincus;
                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(positionCibleFirst);
                        }

                        if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                            if (plateau[positionCibleSecond] != nullptr) {
                                pvRetire = plateau[positionCibleSecond]->subPV(atq);
                                afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCibleSecond], positionCibleSecond);
                                if (plateau[positionCibleSecond]->estVaincu()) {
                                    vaincus.push_back(positionCibleSecond);
                                }
                            }
                            else if ( (positionCibleSecond) == indiceMAX ) {
                                pvRetire = joueur->subPvBase(atq);
                                afficheAttaqueBase(this, getNomUnite(), pvRetire, i);
                            }
                        }

                        autreAction = false;
                        return std::make_pair(false, vaincus);
                
                    }
                }
                else if ( positionCibleFirst == indiceMAX ) {
                    pvRetire = joueur->subPvBase(atq);
                    afficheAttaqueBase(this, getNomUnite(), pvRetire, i);
                    autreAction = false;
                }
            }
        }
        else {

            if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                std::vector<int> vaincus;

                if (plateau[positionCibleSecond] != nullptr) {
                    if (plateau[positionCibleSecond]->getCamp() != getCamp()) {
                        pvRetire = plateau[positionCibleSecond]->subPV(atq);
                        afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCibleSecond], positionCibleSecond);
                        
                        if (plateau[positionCibleSecond]->estVaincu()) {
                            vaincus.push_back(positionCibleSecond);
                        }
                        autreAction = false;
                    }
                }
                else if ( (positionCibleSecond) == indiceMAX ) {
                    pvRetire = joueur->subPvBase(atq);
                    afficheAttaqueBase(this, getNomUnite(), pvRetire, i);
                    autreAction = false;
                }

                if (!autreAction) {
                    if (plateau[positionCibleFirst] != nullptr) {
                        pvRetire = plateau[positionCibleFirst]->subPV(atq);
                        afficheAttaqueUnite(this, getNomUnite(), pvRetire, i, plateau[positionCibleFirst], positionCibleFirst);

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