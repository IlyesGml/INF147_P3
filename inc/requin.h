#ifndef REQUIN_H
#define REQUIN_H
/**
 * @file requin.h
 * @brief Fichier d'en-tête pour la gestion des requins dans la simulation de l'océan.
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
 * - initialise_requin : Initialise la liste des requins.
 * - nouveau_requin : Ajoute un nouveau requin à la liste.
 * - mort_requin : Retire un requin de la liste.
 * - deplacer_requin_1_case : Déplace un requin d'une case dans l'océan.
 */
// Inclusion des en-têtes nécessaires
#include "main.h"

#define MAX_AGE_REQUIN 1500 // Âge maximal du requin
#define NB_JRS_PUB_REQUIN 90 // Nombre de jours avant la puberté
#define NB_JRS_GEST_REQUIN 30 // Nombre de jours de gestation
#define ENERGIE_DIGESTION 10 // Valeur ajoutée à l'indice d?énergie après un repas

//====== STRUCTURE DEFINITION ===//
typedef t_liste t_liste_requin;

//====== PROTOTYPES DES FONCTIONS ===//
/**
 * @brief Initialise la liste des requins dans l'océan.
 *
 * Cette fonction initialise la liste des requins en définissant leur nombre et leur position initiale.
 *
 * @param tete_requin Pointeur vers la tête de la liste des requins à initialiser.
 * @param ocean Pointeur vers l'océan où les requins seront placés.
 * @param quantite Nombre de requins à initialiser.
 * @return Code de succès ou d'erreur.
 */
int initialise_requin(t_liste_requin** tete_requin, t_ocean* ocean, int quantite);

/**
 * @brief Déplace un requin d'une case dans l'océan.
 *
 * Cette fonction déplace un requin d'une case dans l'océan en mettant à jour ses coordonnées.
 *
 * @param requin Pointeur vers le n?ud représentant le requin à déplacer.
 * @param ocean Pointeur vers l'océan où le requin se déplace.
 * @return Code de succès ou d'erreur.
 */
int deplacer_requin_1_case(t_noeud* requin, t_ocean *ocean);

/**
 * @brief Ajoute un nouveau requin à la liste des requins.
 *
 * Cette fonction ajoute un nouveau requin à la liste des requins en fonction de son parent et de l'océan.
 *
 * @param liste Pointeur vers la liste des requins.
 * @param parent Pointeur vers le requin parent.
 * @param ocean Pointeur vers l'océan où le nouveau requin sera ajouté.
 * @return Code de succès ou d'erreur.
 */
int nouveau_requin(t_liste_requin** liste, t_animal* parent, t_ocean* ocean);

/**
 * @brief Retire un requin de la liste des requins.
 *
 * Cette fonction retire un requin de la liste des requins et met à jour l'océan en conséquence.
 *
 * @param liste Pointeur vers la liste des requins.
 * @param ocean Pointeur vers l'océan où le requin sera retiré.
 * @return Code de succès ou d'erreur.
 */
int mort_requin(t_liste_requin** liste, t_ocean* ocean);
/**
 * @brief Compte le nombre de requins dans la liste.   
 * 
 * Cette fonction compte le nombre de requins dans la liste des requins.
 * 
 * @param liste Pointeur vers la tete de la liste des requins.
 * @return Le nombre de requins dans la liste.
 */
int compter_requins(t_liste_requin* liste);

/**
 * @brief Déplace tous les requins de la liste d'une case dans l'océan.
 *
 * Cette fonction déplace tous les requins de la liste d'une case dans l'océan.
 *
 * @param liste Pointeur vers la tête de la liste des requins à déplacer.
 * @param ocean Pointeur vers l'océan où les requins se déplacent.
 * @return Code de succès ou d'erreur.
 */
int deplacer_tout_les_requins (t_liste_requin** liste, t_ocean* ocean);
#endif // REQUIN_H
