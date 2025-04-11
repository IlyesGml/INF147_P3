#ifndef REQUIN_H
#define REQUIN_H
/**
 * @file requin.h
 * @brief Fichier d'en-t�te pour la gestion des requins dans la simulation de l'oc�an.
 *
 * Ce fichier contient les d�finitions, constantes et prototypes de fonctions n�cessaires
 * pour g�rer la liste des requins dans la simulation de l'oc�an. Il inclut les fonctionnalit�s
 * pour initialiser la liste des requins, d�placer les requins, g�rer leur reproduction,
 * et les retirer de la liste.
 *
 * Constantes :
 * - MAX_AGE_REQUIN : �ge maximal d'un requin.
 * - NB_JRS_PUB_REQUIN : Nombre de jours avant qu'un requin atteigne la pubert�.
 * - NB_JRS_GEST_REQUIN : Nombre de jours de gestation pour un requin.
 * - ENERGIE_DIGESTION : �nergie gagn�e par un requin apr�s un repas.
 *
 * Fonctions :
 * - initialise_requin : Initialise la liste des requins.
 * - nouveau_requin : Ajoute un nouveau requin � la liste.
 * - mort_requin : Retire un requin de la liste.
 * - deplacer_requin_1_case : D�place un requin d'une case dans l'oc�an.
 */
// Inclusion des en-t�tes n�cessaires
#include "main.h"

#define MAX_AGE_REQUIN 1500 // �ge maximal du requin
#define NB_JRS_PUB_REQUIN 90 // Nombre de jours avant la pubert�
#define NB_JRS_GEST_REQUIN 30 // Nombre de jours de gestation
#define ENERGIE_DIGESTION 10 // Valeur ajout�e � l'indice d?�nergie apr�s un repas

//====== STRUCTURE DEFINITION ===//
typedef t_liste t_liste_requin;

//====== PROTOTYPES DES FONCTIONS ===//
/**
 * @brief Initialise la liste des requins dans l'oc�an.
 *
 * Cette fonction initialise la liste des requins en d�finissant leur nombre et leur position initiale.
 *
 * @param tete_requin Pointeur vers la t�te de la liste des requins � initialiser.
 * @param ocean Pointeur vers l'oc�an o� les requins seront plac�s.
 * @param quantite Nombre de requins � initialiser.
 * @return Code de succ�s ou d'erreur.
 */
int initialise_requin(t_liste_requin** tete_requin, t_ocean* ocean, int quantite);

/**
 * @brief D�place un requin d'une case dans l'oc�an.
 *
 * Cette fonction d�place un requin d'une case dans l'oc�an en mettant � jour ses coordonn�es.
 *
 * @param requin Pointeur vers le n?ud repr�sentant le requin � d�placer.
 * @param ocean Pointeur vers l'oc�an o� le requin se d�place.
 * @return Code de succ�s ou d'erreur.
 */
int deplacer_requin_1_case(t_noeud* requin, t_ocean *ocean);

/**
 * @brief Ajoute un nouveau requin � la liste des requins.
 *
 * Cette fonction ajoute un nouveau requin � la liste des requins en fonction de son parent et de l'oc�an.
 *
 * @param liste Pointeur vers la liste des requins.
 * @param parent Pointeur vers le requin parent.
 * @param ocean Pointeur vers l'oc�an o� le nouveau requin sera ajout�.
 * @return Code de succ�s ou d'erreur.
 */
int nouveau_requin(t_liste_requin** liste, t_animal* parent, t_ocean* ocean);

/**
 * @brief Retire un requin de la liste des requins.
 *
 * Cette fonction retire un requin de la liste des requins et met � jour l'oc�an en cons�quence.
 *
 * @param liste Pointeur vers la liste des requins.
 * @param ocean Pointeur vers l'oc�an o� le requin sera retir�.
 * @return Code de succ�s ou d'erreur.
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
 * @brief D�place tous les requins de la liste d'une case dans l'oc�an.
 *
 * Cette fonction d�place tous les requins de la liste d'une case dans l'oc�an.
 *
 * @param liste Pointeur vers la t�te de la liste des requins � d�placer.
 * @param ocean Pointeur vers l'oc�an o� les requins se d�placent.
 * @return Code de succ�s ou d'erreur.
 */
int deplacer_tout_les_requins (t_liste_requin** liste, t_ocean* ocean);
#endif // REQUIN_H
