#include "catapulte.hpp"

int Catapulte::prix = 20;
int Catapulte::atq = 6;
std::pair<int,int> Catapulte::portee[3] = {std::make_pair(2,3), std::make_pair(3,4), std::make_pair(3,4)};

Catapulte::~Catapulte() {}

/**
 * Redéfinition de la méthode attaque
 * Simule l'attaque d'une Catapulte
 * Affiche la/les attaque(s) d'une Catapulte si elles a/ont eu lieu
 * 
 * @param *plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 * @param *joueur pointeur sur le Joueur adverse
 * @return un vecteur d'indices du tableau, correspondant aux unités vaincus
 */
std::vector<int> Catapulte::attaque(Unite* plateau[12], int i, Joueur* joueur) {

    int indiceMAX; // représente l'indice de la base adverse
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    for (int j=0; j<3; j++) {
        int positionCibleFirst = i + getCamp() * portee[j].first; // représente l'indice du premier ennemi sur les deux touchés par l'attaque, potentiellement attaquables
        int positionCibleSecond = i + getCamp() * portee[j].second; // représente l'indice du deuxième ennemi sur les deux touchés par l'attaque, potentiellement attaquables
        int pvRetire; // représente le nombre de points de vie retirés à la cible

        if (j != 2) {

            if ( ((getCamp() == 1) && ((positionCibleFirst) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleFirst) >= indiceMAX)) ) {
                if (plateau[positionCibleFirst] != nullptr) {
                    if (plateau[positionCibleFirst]->getCamp() != getCamp()) {
                        pvRetire = plateau[positionCibleFirst]->subPV(atq);
                        afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCibleFirst], positionCibleFirst);

                        std::vector<int> vaincus; // représente les indices du tableau des unités vaincus
                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(positionCibleFirst);
                        }

                        if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                            if (plateau[positionCibleSecond] != nullptr) {
                                pvRetire = plateau[positionCibleSecond]->subPV(atq);
                                afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCibleSecond], positionCibleSecond);
                                if (plateau[positionCibleSecond]->estVaincu()) {
                                    vaincus.push_back(positionCibleSecond);
                                }
                            }
                            else if (positionCibleSecond == indiceMAX) {
                                pvRetire = joueur->subPvBase(atq);
                                afficheAttaqueBase(getNomUnite(), pvRetire, i);
                            }
                        }

                        setAutreAction(false);
                        return vaincus;
                
                    }
                }
                else if (positionCibleFirst == indiceMAX) {
                    pvRetire = joueur->subPvBase(atq);
                    afficheAttaqueBase(getNomUnite(), pvRetire, i);
                    setAutreAction(false);
                }
            }
        }
        else {

            if ( ((getCamp() == 1) && ((positionCibleSecond) <= indiceMAX)) || ((getCamp() == -1) && ((positionCibleSecond) >= indiceMAX)) ) {
                std::vector<int> vaincus;

                if (plateau[positionCibleSecond] != nullptr) {
                    if (plateau[positionCibleSecond]->getCamp() != getCamp()) {
                        pvRetire = plateau[positionCibleSecond]->subPV(atq);
                        afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCibleSecond], positionCibleSecond);
                        
                        if (plateau[positionCibleSecond]->estVaincu()) {
                            vaincus.push_back(positionCibleSecond);
                        }
                        setAutreAction(false);
                    }
                }
                else if (positionCibleSecond == indiceMAX) {
                    pvRetire = joueur->subPvBase(atq);
                    afficheAttaqueBase(getNomUnite(), pvRetire, i);
                    setAutreAction(false);
                }

                if (!getAutreAction()) {
                    if (plateau[positionCibleFirst] != nullptr) {
                        pvRetire = plateau[positionCibleFirst]->subPV(atq);
                        afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCibleFirst], positionCibleFirst);

                        if (plateau[positionCibleFirst]->estVaincu()) {
                            vaincus.push_back(positionCibleFirst);
                        }
                    }
                }
                return vaincus;
            }
        }
    }
    return std::vector<int>()={};
}

/**
 * Redéfinition de la méthode deplace
 * Déplace un pointeur de Catapulte vers une case adjacente du tableau de pointeurs d'Unite
 * Affiche les caractéristiques du déplacement
 * 
 * @param *plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 */
void Catapulte::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new Catapulte( plateau[i]->getCamp(), plateau[i]->getPV());
	std::cout << *(plateau[i]) << "(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}