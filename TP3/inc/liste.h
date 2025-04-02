#ifndef LISTE_H
#define LISTE_H

#include "main.h"


#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Taille maximale de la liste

// D�finition de la structure de la liste statique
typedef struct {
    t_animal animal[MAX]; // Tableau contenant les �l�ments
    int taille;        // Nombre actuel d'�l�ments dans la liste
} t_liste;

// Fonctions pour g�rer la liste statique
void init_liste(t_liste* l);
int inserer(t_liste* l, t_animal valeur, int position);
int supprimer(t_liste* l, int position);
int obtenir(t_liste* l, int position, t_animal* valeur);
void decalage_gauche(t_liste* l, int position);
void decalage_droite(t_liste* l, int position);
void afficher_liste(const t_liste* l);




#endif // LISTE_H