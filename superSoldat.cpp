#include "superSoldat.hpp"

SuperSoldat::~SuperSoldat() {}

/**
 * Redéfinition de la méthode attaque
 * Simule l'attaque d'un SuperSoldat
 * Affiche l'attaque d'un SuperSoldat si elle a eu lieu
 * 
 * @param *plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 * @param *joueur pointeur sur le Joueur adverse
 * @return un vecteur d'indices du tableau, correspondant aux unités vaincus
 */
std::vector<int> SuperSoldat::attaque(Unite* plateau[12], int i, Joueur* joueur) {

    int indiceMAX; // représente l'indice de la base adverse
    if (getCamp() == 1) {
        indiceMAX = 11;
    }
    else {
        indiceMAX = 0;
    }

    int positionCible = i + getCamp() * getPortee(); // représente l'indice d'un ennemi potentiellement attaquable
    int pvRetire; // représente le nombre de points de vie retirés à la cible

    if (plateau[positionCible] != nullptr) {
        if (plateau[positionCible]->getCamp() != getCamp()) {
            pvRetire = plateau[positionCible]->subPV(Fantassin::getAtq());
            afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
            
            if (plateau[positionCible]->estVaincu()) {
            	return std::vector<int>(1)={i+ getCamp()};
            }
        }
    }
    else if ( positionCible == indiceMAX ) {
        pvRetire = joueur->subPvBase(Fantassin::getAtq());
        afficheAttaqueBase(getNomUnite(), pvRetire, i);
    }
    return std::vector<int>()={};
}

/**
 * Redéfinition de la méthode deplace
 * Déplace un pointeur de SuperSoldat vers une case adjacente du tableau de pointeurs d'Unite
 * Affiche les caractéristiques du déplacement
 *
 * @param *plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 */
void SuperSoldat::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new SuperSoldat(plateau[i]->getCamp(), plateau[i]->getPV());
	std::cout << *(plateau[i]) << "(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}