#ifndef POISSON_H
#define POISSON_H

#include "main.h"
// poisson.h
// Ce fichier contient les déclarations des structures et des fonctions nécessaires pour gérer les poissons
// dans un environnement océanique simulé. Les fonctionnalités incluent :
//
// 1. Création de la liste initiale des poissons :
//    - Génère un nombre spécifié de poissons dans des cases vides aléatoires de l'océan.
//    - Chaque poisson est initialisé avec un âge aléatoire, une énergie de départ, et 0 jours de gestation.
//    - Les poissons sont également ajoutés à l'océan.
//
// 2. Déplacement des poissons :
//    - Permet à un poisson de se déplacer d'une case dans son voisinage immédiat, si une case libre est disponible.
//    - Les déplacements horizontaux sont cycliques (traversée d'un bord à l'autre).
//    - Les modifications sont reflétées dans l'océan.
//
// 3. Ajout de nouveaux poissons :
//    - Permet à un poisson-parent de générer un bébé-poisson dans une case voisine libre, sous certaines conditions.
//    - Gère les probabilités de fausse-couche et les contraintes de surpopulation.
//    - Met à jour les attributs du poisson-parent et ajoute le bébé-poisson à la liste et à l'océan.
//
// 4. Élimination des poissons :
//    - Supprime un poisson de la liste et vide sa position dans l'océan.
//
// Ce module est conçu pour simuler la dynamique des populations de poissons dans un environnement océanique,
// tout en respectant les contraintes biologiques et environnementales définies.
// Ce fichier contient les déclarations des fonctions pour gérer les poissons dans l'océan.
// Les fonctions incluent la création de la liste initiale des poissons, le déplacement des poissons,
// l'ajout de nouveaux poissons et l'élimination des poissons de la liste.

#define MAX_POISSON 1000 //nombre maximal de poissons avant la surpopulation
#define MAX_AGE_POISSON 150 //âge maximal du poisson
#define NB_JRS_PUB_POISSON 30 //nombre de jours avant la puberté
#define NB_JRS_GEST_POISSON 15 //nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3 //valeur initiale d'énergie

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
/** 
 * @brief Structure représentant un poisson.
 * Cette structure représente un poisson dans l'océan, avec ses attributs tels que l'âge, la gestation,
 * l'énergie, et sa position dans l'océan.
 */
typedef t_liste t_liste_poisson;
//====== PROTOTYPES ===//
/**
 * @brief Initialise la liste des poissons.
 * 
 * Cette fonction initialise la liste des poissons en définissant le nombre de poissons à zéro.
 * 
 * @param poisson Pointeur vers la liste des poissons à initialiser.
 */
int initialise_poisson(t_liste_poisson** tete_poisson, t_ocean* ocean, int quantite);
/**
 * @brief Déplace un poisson dans l'océan.
 * 
 * Cette fonction déplace un poisson à une position donnée dans l'océan.
 * 
 * @param poisson Pointeur vers la liste des poissons.
 * @param position Position du poisson à déplacer.
 * @param x Nouvelle position x du poisson.
 * @param y Nouvelle position y du poisson.
 */
int deplacer_poisson_1_case(t_noeud* poisson, t_ocean *ocean);
/**
 * @brief Ajoute un nouveau poisson à la liste.
 * 
 * Cette fonction ajoute un nouveau poisson à la liste des poissons à une position donnée.
 * 
 * @param poisson Pointeur vers la liste des poissons.
 * @param nouveau_poisson Pointeur vers le nouveau poisson à ajouter.
 * @param position Position où ajouter le nouveau poisson.
 */
int mort_poisson(t_liste_poisson** liste, t_ocean* ocean);
/**
 * @brief Retire un poisson de la liste.
 * 
 * Cette fonction retire un poisson de la liste des poissons à une position donnée.
 * 
 * @param poisson Pointeur vers la liste des poissons.
 * @param position Position du poisson à retirer.
 */
int compter_poissons(t_liste_poisson* liste);


#endif // POISSON_H