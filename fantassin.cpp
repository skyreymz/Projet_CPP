#include "fantassin.hpp"
#include "superSoldat.hpp"

int Fantassin::prix = 10;
int Fantassin::atq = 4;
int Fantassin::portee[1] = {1};

Fantassin::~Fantassin() {}

/**
 * Redéfinition de la méthode attaque
 * Simule l'attaque d'un Fantassin et le transforme en SuperSoldat s'il vainc un Fantassin ennemi
 * 
 * @param plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 * @param joueur pointeur sur le Joueur adverse
 * @return un vecteur d'indices du tableau, correspondant aux unités vaincus
 */
std::vector<int> Fantassin::attaque(Unite* plateau[12], int i, Joueur* joueur) {

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

            pvRetire = plateau[positionCible]->subPV(atq);
            afficheAttaqueUnite(getNomUnite(), pvRetire, i, plateau[positionCible], positionCible);
            setAutreAction(false);

            if (plateau[positionCible]->estVaincu()) {
                if (aVaincuFantassin(plateau[positionCible])) {
                    // on évolue le Fantassin s'il a vaincu un Fantassin ennemi
				    int pv = plateau[i]->getPV();
                    int camp = plateau[i]->getCamp(); 
				    delete plateau[i];
				    plateau[i] = new SuperSoldat(camp, pv);
                }
                return std::vector<int>(1)={positionCible};
            }
        }
    }
    else if (positionCible == indiceMAX) {
        pvRetire = joueur->subPvBase(atq);
        afficheAttaqueBase(getNomUnite(), pvRetire, i);
        setAutreAction(false);
    }
    return std::vector<int>()={};
}

/**
 * Vérifie si l'objet passé en paramètre est un Fantassin
 * 
 * @param unite Unite dont on veut vérifier le type
 * @return true si l'objet passé en paramètre est un Fantassin, false sinon
 */
bool Fantassin::aVaincuFantassin(Unite* unite) { 
    if (unite->getNomUnite() == 'F') {
        std::cout << "Transformation de " << *unite << " en Super-Soldat" << std::endl;
        return true;
    }
    else {
        return false;
    }
}

/**
 * Redéfinition de la méthode deplace
 * Déplace un pointeur de Fantassin vers une case adjacente du tableau de pointeurs d'Unite
 * 
 * @param plateau tableau de pointeurs d'Unite de taille fixée à 12, contient les pointeurs d'Unite selon leur position en jeu
 * @param i entier correspondant à l'indice de l'Unite courante en jeu
 */
void Fantassin::deplace(Unite* plateau[12], int i) {
    plateau[i + getCamp()] = new Fantassin(plateau[i]->getCamp(), plateau[i]->getPV(), plateau[i]->getAutreAction());
	std::cout << *(plateau[i]) << "(position " << i << ") a avancé à la position " << i+getCamp() << std::endl;
	delete plateau[i];
	plateau[i] = nullptr;
}