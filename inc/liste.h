#ifndef LISTE_H
#define LISTE_H

#include "main.h"


#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Taille maximale de la liste

// Définition de la structure de la liste statique
/**
 * @brief structure représentant un noeud de la liste.
 * @param animal t_animal représentant un objet poisson ou un requin.
 * @param precedent Pointeur vers le noeud précédent.
 * @param suivant Pointeur vers le noeud suivant.
 */
typedef struct t_noeud {
    t_animal animal; // Tableau contenant les éléments
    struct t_noeud* precedent;    // Pointeur vers le noeud précédent
    struct t_noeud* suivant;        // Nombre actuel d'éléments dans la liste
} t_liste;

// Fonctions pour gérer la liste statique
t_noeud* creer_noeud(t_animal animal);
t_noeud* insererEnTete(t_liste** liste, t_animal animal);
void supprimerEnTete(t_liste** liste);
void supprimerAnimal(t_noeud** tete ,t_noeud* animal_to_kill);
void libererListe(t_liste* liste);
void afficherListe(t_liste* liste);
t_noeud* insererEnFin(t_liste** liste, t_animal animal);




#endif // LISTE_H