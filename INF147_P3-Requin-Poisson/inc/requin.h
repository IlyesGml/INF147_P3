#ifndef REQUIN_H
#define REQUIN_H
/**
 * @file requin.h
 * @brief Fichier d'en-tête pour la gestion du module des requins dans la simulation de l'océan.
 *
 * Ce fichier contient les définitions, constantes et prototypes de fonctions nécessaires
 * pour gérer la liste des requins dans la simulation de l'océan. Il inclut les fonctionnalités
 * pour initialiser la liste des requins, déplacer les requins, gérer leur reproduction,
 * et les retirer de la liste.
 *
 * Constantes :
 * - MAX_AGE_REQUIN : Âge maximal d'un requin.
 * - NB_JRS_PUB_REQUIN : Nombre de jours avant qu'un requin atteigne la puberté.
 * - NB_JRS_GEST_REQUIN : Nombre de jours de gestation pour un requin.
 * - ENERGIE_DIGESTION : Énergie gagnée par un requin après un repas.
 *
 * Fonctions :
 * - init_requin : Initialise la liste des requins.
 * - nouveau_requin : Ajoute un nouveau requin à la liste.
 * - mort_requin : Retire un requin de la liste.
 * - deplacement_requin : Déplace un requin dans l'océan.
 */
// Inclusion des en-têtes nécessaires
#include "main.h"

#define MAX_AGE_REQUIN 1500 //âge maximal du requin
#define NB_JRS_PUB_REQUIN 90 //nombre de jours avant la puberté
#define NB_JRS_GEST_REQUIN 30 //nombre de jours de gestation
#define ENERGIE_DIGESTION 10 //valeur ajoutée à l'indice d’énergie après un repas


//====== STRUCTURE ANIMAL ===//
/*
typedef struct {
    int age; // Age de l'animal
    int jrs_gest; // Jours de gestation
    int energie_sante; // Energie de l'animal
    int x; // Position x de l'animal
    int y; // Position y de l'animal
} t_animal;
*/
//====== STRUCTURE DEFINITION ===//
typedef t_liste t_liste_requin;
//====== PROTOTYPES DES FONCTIONS ===//

int initialise_requin(t_liste_requin** tete_requin, t_ocean* ocean, int quantite);

int deplacer_requin_1_case(t_noeud* requin, t_ocean *ocean);

int mort_requin(t_liste_requin** liste, t_ocean* ocean);

int compter_requins(t_liste_requin* liste);

int nouveau_requin(t_liste_requin** liste, t_animal* parent, t_ocean* ocean);


#endif // REQUIN_H